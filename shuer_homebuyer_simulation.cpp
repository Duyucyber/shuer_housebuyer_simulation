#include <array>
#include <iomanip>
#include <iostream>

class Salary {
public:
    explicit Salary(long double initialIncome) : annualIncome_(initialIncome) {}

    long double annualIncome() const {
        return annualIncome_;
    }

    void advanceYear() {
    if (annualIncome_ < salaryThreshold_) {
        annualIncome_ *= highGrowthRate_;
    } else {
        annualIncome_ *= lowGrowthRate_;
    }
    }

private:
    long double annualIncome_;
    static constexpr long double salaryThreshold_ = 600000.0L;
    static constexpr long double highGrowthRate_ = 1.15L;
    static constexpr long double lowGrowthRate_ = 1.05L;
};

class House {
public:
    explicit House(long double initialPrice) : price_(initialPrice) {}

    void appreciateOneYear() {
        price_ *= annualGrowthRate_;
    }

    long double downPayment() const {
        return price_ * downPaymentRate_;
    }

    long double price() const {
        return price_;
    }

private:
    long double price_;
    static constexpr long double annualGrowthRate_ = 1.10L;
    static constexpr long double downPaymentRate_ = 0.30L;
};

class SHUer {
public:
    SHUer(long double initialIncome, long double initialHousePrice,
              long double savingsRate)
        : salary_(initialIncome), house_(initialHousePrice),
          savingsRate_(savingsRate), savings_(0.0L) {}

    int yearsToDownPayment(int maxYears) {
        for (int year = 1; year <= maxYears; ++year) {
            savings_ += salary_.annualIncome() * savingsRate_;
            house_.appreciateOneYear();

            if (savings_ >= house_.downPayment()) {
                return year;
            }

            salary_.advanceYear();
        }
        return -1;
    }

    long double savings() const {
        return savings_;
    }

    long double housePrice() const {
        return house_.price();
    }

    long double requiredDownPayment() const {
        return house_.downPayment();
    }

private:
    Salary salary_;
    House house_;
    long double savingsRate_;
    long double savings_;
};

int main() {
    constexpr long double initialIncome = 300000.0L;
    constexpr long double initialHousePrice = 5000000.0L;
    constexpr int maxSimulationYears = 1000;
    const std::array<long double, 3> savingsRates = {0.70L, 0.80L, 0.90L};

    std::cout << "假设：毕业第一年收入为30万元；每年年末存下当年收入的一定比例，"
                 "不计利息；房价从毕业时起每年上涨10%。\n"
                 "收入每年上涨15%，达到60万元后改为每年上涨5%。\n\n";
    std::cout << std::fixed << std::setprecision(2);

    for (long double rate : savingsRates) {
        SHUer buyer(initialIncome, initialHousePrice, rate);
        const int years = buyer.yearsToDownPayment(maxSimulationYears);

        std::cout << "储蓄比例 " << static_cast<int>(rate * 100) << "%：";
        if (years >= 0) {
            std::cout << years << " 年；届时累计储蓄 "
                      << buyer.savings() / 10000.0L << " 万元，房价 "
                      << buyer.housePrice() / 10000.0L << " 万元，首付 "
                      << buyer.requiredDownPayment() / 10000.0L << " 万元。\n";
        } else {
            std::cout << "在 " << maxSimulationYears
                      << " 年的模拟范围内未攒够首付。\n";
        }
    }

    return 0;
}
