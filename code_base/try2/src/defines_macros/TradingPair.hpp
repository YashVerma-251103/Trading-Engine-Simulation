#include "./imports.hpp"

struct TradingPair
{
    // BTC-USD
    // BTC => BASE
    // USD => QUOTE
    // Amount of quote one is will to give to obtain base

    // TradingPair Attributes
    string base, quote;

    // Constructor
    TradingPair() : base("Basky"), quote("Qosky") {}
    TradingPair(string base, string quote) : base(base), quote(quote) {}

    bool operator==(const TradingPair &otherPair) const
    {
        return ((base == otherPair.base) && (quote == otherPair.quote));
    }

    void printMarketPair() const
    {
        print("\n\nNew Market => Base : " << base << " | Quote : " << quote);
    }
};

namespace std
{
    template <>
    struct hash<TradingPair>
    {
        auto operator()(const TradingPair &tp) const
        {
            return ((Hash<string>()(tp.base)) ^ (Hash<string>()(tp.quote) << 1));
        }
    };
} // namespace std
