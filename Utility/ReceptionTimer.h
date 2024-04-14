#pragma once

class ReceptionTimer
{
public:
    /**
     * @param receptionTime 受付時間
     * @param startTime     受付開始までの時間
     */
    ReceptionTimer(float receptionTime, float startTime = 0.0f);

    /**
     * @brief 経過した時間が受付時間か確認
     * @param elapsedTime 経過時間
     * @return true : 受付時間内
     * @return false : 受付時間外
     */
    bool Reception(float elapsedTime) const;

    /**
     * @brief 受付時間を取得
     */
    float ReceptionTime() const;

    /**
     * @brief 受付時間を設定
     * @param time
     */
    void ReceptionTime(float time);

    /**
     * @brief 受付開始までの時間を取得
     */
    float StartTime() const;

    /**
     * @brief 受付開始までの時間を設定
     * @param time
     */
    void StartTime(float time);

private:
    float receptionTime_;
    float startTime_;
};
