// * Import header file
#include "Order.hpp"

// * Structure for Limit.
struct Limit
{
    // ? Attributes
    shPtr(Price) price;
    vector<shPtr(Order)> orders = vector<shPtr(Order)>();
    float total_volume = 0.0f;

    // ? Constructors
    Limit()
    {
        this->price = shObj(Price)();
    }
    Limit(float price)
    {
        assert(price > 0);

        this->price = shObj(Price)(price);
    }
    Limit(float *price)
    {
        assert(price != nullptr && *price > 0);

        this->price = shObj(Price)(*price);
    }

    // ? Functional Utilities
    void printCurrentOrders()
    {
        for (size_t i = 0; i < orders.size(); i++)
            orders[i]->printOrder();
    }
    void addOrder(shPtr(Order) newOrder)
    {
        assert(newOrder != nullptr);

        orders.push_back(newOrder);
        total_volume += newOrder->size;
    }
    bool fillOrder(shPtr(Order) marketOrder)
    {
        assert(marketOrder != nullptr);

        // ! checking if the market order can even be filled or not.
        if (marketOrder->size > total_volume)
        {
            return not_filled;
        }

        assert(marketOrder->size <= total_volume);
        for (auto &limitOrder : orders)
        {
            if (marketOrder->size >= limitOrder->size)
            {
                marketOrder->size -= limitOrder->size;
                total_volume -= limitOrder->size;
                limitOrder->size = 0.0f;
            }
            else
            {
                limitOrder->size -= marketOrder->size;
                total_volume -= marketOrder->size;
                marketOrder->size = 0.0f;
            }

            if (marketOrder->isFilled())
            {
                break;
            }
        }
        return filled;
    }

    // ! Struct utilities
    static void vector_merge(vector<shPtr(Price)> *list, bool *reverse, int start, int mid, int end)
    {
        vector<shPtr(Price)> sorted_list = vector<shPtr(Price)>();

        int i = start, j = mid;
        shPtr(Price) A, B;
        // Price *A,*B;
        bool order = (*reverse) ? (*A > *B) : (*B > *A);
        while (i < mid && j <= end)
        {
            A = (*list)[i];
            B = (*list)[j];

            if ((*A) == (*B))
            {
                sorted_list.push_back(A);
                i++;
                sorted_list.push_back(B);
                j++;
            }
            else if (order)
            {
                sorted_list.push_back(B);
                j++;
            }
            else
            {
                sorted_list.push_back(A);
                i++;
            }
        }
        while (*reverse && j <= end)
            sorted_list.push_back((*list)[j++]);
        while (i < mid)
            sorted_list.push_back((*list)[i++]);
        while (!(*reverse) && j <= end)
            sorted_list.push_back((*list)[j++]);

        i = start;
        for (const auto &price : sorted_list)
            (*list)[i++] = price;

        // TODO: check if the sortedlist vector needs to freed here. If yes then how ?
    }
    static void vector_sort(vector<shPtr(Price)> *list, bool *reverse, int start, int end)
    {
        if (start == end)
            return;
        if (start < end)
        {
            int mid = (int)(((end - start) / 2) + start);
            vector_sort(list, reverse, start, mid);
            vector_sort(list, reverse, mid + 1, end);
            vector_merge(list, reverse, start, mid, end);
        }
    }
    static void linear_sort(vector<shPtr(Limit)> *list, vector<shPtr(Limit)> *sorted_list, bool *reverse)
    {
        int len = list->size();
        list->clear();
        switch (*reverse)
        {
        case true:
            for (auto i = 0; i < len; i++)
                list->push_back((*sorted_list)[i]);
            break;

        case false:
            for (auto i = len - 1; i >= 0; i--)
                list->push_back((*sorted_list)[i]);
            break;
        }
    }
};