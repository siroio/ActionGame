#pragma once
#include <Singleton.h>

class Fuzzy
{
private:
    Fuzzy() = default;
    ~Fuzzy() = default;

public:
    Fuzzy(const Fuzzy&) = delete;
    Fuzzy& operator=(const Fuzzy&) = delete;
    Fuzzy(Fuzzy&&) = delete;
    Fuzzy& operator=(Fuzzy&&) = delete;

public:
    /**
     * @brief 右上がりのグラフメンバーシップ関数
     * @param value 評価対象
     * @param min 最低値
     * @param max 最大値
     * @return 評価値
     */
    static float Grade(float value, float min, float max);

    /**
     * @brief 右下がりのメンバーシップ関数
     * @param value 評価対象
     * @param min 最低値
     * @param max 最大値
     * @return 評価値
     */
    static float ReverseGrade(float value, float min, float max);

    /**
     * @brief 三角形型のグラフのメンバーシップ関数
     * @param value 評価対象
     * @param left 左端値
     * @param mid 中央値
     * @param right 右端値
     * @return 評価値
     */
    static float Triangle(float value, float left, float mid, float right);

    /**
     * @brief 台形のグラフのメンバーシップ関数
     * @param value 評価対象
     * @param downL 台形下部の左端値
     * @param upperL 台形上部の左側値
     * @param upperR 台形上部の右側値
     * @param downR 台形下部の右側値
     * @return 評価値
     */
    static float Trapezoid(float value, float downL, float upperL, float upperR, float downR);

    /**
     * @brief ファジー理論AND演算子
     * @param lhs 評価対象1
     * @param rhs 評価対象2
     * @return 評価値
     */
    static float AND(float lhs, float rhs);

    /**
     * @brief ファジー理論OR演算子
     * @param lhs 評価対象1
     * @param rhs 評価対象2
     * @return 評価値
     */
    static float OR(float lhs, float rhs);

    /**
     * @brief ファジー理論NOT演算子
     * @param value 評価対象
     * @return 評価値
     */
    static float NOT(float value);
};
