#pragma once
#include <concepts>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <typeindex>
#include <memory>
#include <GearsUtility/WeakPtr.h>
#include <GearsDebug/Debugger.h>
#include <string>

template<class Context, class Event>
class StateMachine
{
public:
    class State
    {
    public:
        State(StateMachine<Context, Event>& stateMachine, Context& context) :
            stateMachine_{ stateMachine }, context_{ context }
        {}

        virtual void Enter()
        {}
        virtual void FixedUpdate()
        {}
        virtual void Update()
        {}
        virtual void LateUpdate()
        {}
        virtual void Exit()
        {}

        virtual bool GuardEvent(Event eventID)
        {
            return false;
        }

    protected:
        StateMachine<Context, Event>& GetStateMachine()
        {
            return stateMachine_;
        }
        Context& GetContext()
        {
            return context_;
        }

    private:
        friend class StateMachine<Context, Event>;
        std::unordered_map<Event, Glib::WeakPtr<State>> transitionTable_;
        StateMachine<Context, Event>& stateMachine_;
        Context& context_;
    };

private:
    enum class UpdateState
    {
        Idle,
        Enter,
        Update,
        Exit,
    };

public:
    StateMachine(const std::shared_ptr<Context>& context)
    {
        context_ = context;
        updateState_ = UpdateState::Idle;
        allowReTransition_ = false;
    }

    template<class Prev, class Next> requires std::derived_from<Prev, State>&& std::derived_from<Next, State>
    void AddTransition(Event eventID)
    {
        if (IsRun()) return;
        auto prevState = GetOrCreateState<Prev>();
        auto nextState = GetOrCreateState<Next>();

        if (prevState->transitionTable_.contains(eventID)) return;
        prevState->transitionTable_[eventID] = nextState;
    }

    template<class T> requires std::derived_from<T, State>
    void SetStartState()
    {
        // 既にステートマシンが起動してしまっている場合は
        if (IsRun()) return;

        // 次に処理するステートの設定をする
        nextState_ = GetOrCreateState<T>();
    }

    bool SendEvent(Event eventID)
    {
        if (!IsRun()) return false;

        // Exit中は推移できない
        if (updateState_ == UpdateState::Exit) return false;

        // 推移をブロック
        if (nextState_ != nullptr && !allowReTransition_) return false;
        if (currentState_->GuardEvent(eventID)) return false;

        const auto& event = currentState_->transitionTable_.find(eventID);
        if (event == currentState_->transitionTable_.end()) return false;
        nextState_ = event->second;
        return true;
    }

    void Update()
    {
        if (updateState_ != UpdateState::Idle) return;

        if (!IsRun())
        {
            if (nextState_ == nullptr) return;

            currentState_ = nextState_;
            nextState_ = nullptr;
        }

        try
        {
            updateState_ = UpdateState::Enter;
            currentState_->Update();
        }
        catch (const std::exception&)
        {
            nextState_ = currentState_;
            currentState_ = nullptr;
            updateState_ = UpdateState::Idle;
            // TODO: Add Exception Handle
            return;
        }

        if (nextState_ == nullptr)
        {
            updateState_ = UpdateState::Idle;
            return;
        }

        try
        {
            // 次に遷移するステートが存在していないなら
            if (nextState_ == nullptr)
            {
                // Update処理中であることを設定してUpdateを呼ぶ
                updateState_ = UpdateState::Update;
                currentState_->Update();
            }


            // 次に遷移するステートが存在している間ループ
            while (nextState_ != nullptr)
            {
                // Exit処理中であることを設定してExit処理を呼ぶ
                updateState_ = UpdateState::Exit;
                currentState_->Exit();


                // 次のステートに切り替える
                currentState_ = nextState_;
                nextState_ = nullptr;


                // Enter処理中であることを設定してEnterを呼ぶ
                updateState_ = UpdateState::Enter;
                currentState_->Enter();
            }


            // 更新処理が終わったらアイドリングに戻る
            updateState_ = UpdateState::Idle;
        }
        catch (const std::exception&)
        {
            // 更新状態をアイドリングにして、例外発生時のエラーハンドリングを行い終了する
            updateState_ = UpdateState::Idle;
            // TODO: Add Exception Handle
            return;
        }
    }

    bool IsRun() const
    {
        return currentState_ != nullptr;
    }

    bool IsUpdate() const
    {
        return IsRun() && updateState_ != UpdateState::Idle;
    }

    void ReTransition(bool enable)
    {
        allowReTransition_ = enable;
    }

    bool ReTransition() const
    {
        return allowReTransition_;
    }

private:
    template<class T> requires std::derived_from<T, State>
    Glib::WeakPtr<T> GetOrCreateState()
    {
        const auto& state = stateList_.find(typeid(T));
        if (state != stateList_.end())
        {
            return Glib::WeakPtr<T>{ state->second };
        }

        auto newState = std::make_shared<T>(*this, *context_);
        stateList_.emplace(typeid(T), newState);
        return newState;
    }

private:
    UpdateState updateState_;
    std::unordered_map<std::type_index, std::shared_ptr<State>> stateList_;
    Glib::WeakPtr<State> currentState_;
    Glib::WeakPtr<State> nextState_;
    std::shared_ptr<Context> context_;
    bool allowReTransition_{ false };
};
