#ifndef FILE_HARBOR_HPP
#define FILE_HARBOR_HPP
#include "std/string.hpp"
#include "std/vector.hpp"
#include "std/unique_ptr.hpp"
#include "models/ship.hpp"
#include "models/good.hpp"

class Ship;

class Harbor {
public:
    Harbor(String name);
    Harbor(String name, unique_ptr<Vector<Ship*>> shipsForSale,
           unique_ptr<Vector<Good*>> goodsForSale) noexcept;
    Harbor(Harbor&& other) = delete;
    Harbor(const Harbor& other) = delete;
    Harbor& operator=(Harbor&& other) = delete;
    Harbor& operator=(const Harbor& other) = delete;
    ~Harbor() = default;

    String getName() const noexcept;
    Vector<Good*>& getGoodsForSale() const;
    Vector<Ship*>& getShipsForSale() const;
    int getLightCannonStock() const noexcept;
    int getMediumCannonStock() const noexcept;
    int getHeavyCannonStock() const noexcept;
    void setLightCannonStock(int amount) noexcept;
    void setMediumCannonStock(int amount) noexcept;
    void setHeavyCannonStock(int amount) noexcept;
    void randomizeCannonStock();
private:
    String name;
    unique_ptr<Vector<Ship*>> shipsForSale;
    unique_ptr<Vector<Good*>> goodsForSale;
    int lightCannonStock;
    int mediumCannonStock;
    int heavyCannonStock;
};

#endif