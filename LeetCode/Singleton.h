/*
 * @Author: Skye
 * @Date: 2021-08-02 09:11:43
 * @LastEditTime: 2021-08-02 09:25:36
 * @Description: 单例
 * Skye:'Never stop!'
 */

class Singleton {
private:
    Singleton() { }

    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

public:
    static Singleton& GetInstance()
    {
        static Singleton instance;
        return instance;
    }
};