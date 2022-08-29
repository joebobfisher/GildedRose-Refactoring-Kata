#include <gtest/gtest.h>
#include "GildedRose.h"

class GildedRoseTests : public ::testing::Test {
protected:
    void SetUp() override;
    vector<Item> things;
    GildedRose * target;
};

void GildedRoseTests::SetUp() {
    things.emplace_back("Foo", 1, 1);
    target = new GildedRose(things);
}

TEST_F(GildedRoseTests, UpdateQualityDoesNotChangeItemName) {
    target->updateQuality();
    EXPECT_EQ("Foo", target->items[0].name);
}

TEST_F(GildedRoseTests, UpdateQualityDecreasesSellIn) {
    target->updateQuality();
    EXPECT_EQ(0, target->items[0].sellIn);
}

TEST_F(GildedRoseTests, UpdateQualityDecreasesQuality) {
    target->updateQuality();
    EXPECT_EQ(0, target->items[0].quality);
}

TEST_F(GildedRoseTests, UpdateQualityDecreasesQualityTwiceAsFastAfterSellIn) {
    target->items[0].sellIn = 0;
    target->items[0].quality = 2;
    target->updateQuality();
    EXPECT_EQ(0, target->items[0].quality);
}

TEST_F(GildedRoseTests, UpdateQualityDoesNotDecreaseQualityBelowZero) {
    target->items[0].quality = 0;
    target->updateQuality();
    EXPECT_EQ(0, target->items[0].quality);
}

TEST_F(GildedRoseTests, UpdateQualityIncreasesAgedBrieQuality) {
    target->items[0].name = "Aged Brie";
    target->updateQuality();
    EXPECT_EQ(2, target->items[0].quality);
}

TEST_F(GildedRoseTests, UpdateQualityDoesNotUpdateAbove50) {
    target->items[0].name = "Aged Brie";
    target->items[0].quality = 50;
    target->updateQuality();
    EXPECT_EQ(50, target->items[0].quality);
}

TEST_F(GildedRoseTests, UpdateQualitySulfurasDoesNotDegrade) {
    target->items[0].name = "Sulfuras, Hand of Ragnaros";
    target->items[0].quality = 80;
    target->items[0].sellIn = 50;
    target->updateQuality();
    EXPECT_EQ(80, target->items[0].quality);
    EXPECT_EQ(50, target->items[0].sellIn);
}

TEST_F(GildedRoseTests, UpdateQualityIncreasesBackstagePassQualityBy1WhenSellInGreaterThan10) {
    target->items[0].name = "Backstage passes to a TAFKAL80ETC concert";
    target->items[0].sellIn = 11;
    target->updateQuality();
    EXPECT_EQ(2, target->items[0].quality);
}

TEST_F(GildedRoseTests, UpdateQualityIncreasesBackstagePassQualityBy2WhenSellInLE10) {
    target->items[0].name = "Backstage passes to a TAFKAL80ETC concert";
    target->items[0].sellIn = 10;
    target->updateQuality();
    EXPECT_EQ(3, target->items[0].quality);
}

TEST_F(GildedRoseTests, UpdateQualityIncreasesBackstagePassQualityBy3WhenSellInLE5) {
    target->items[0].name = "Backstage passes to a TAFKAL80ETC concert";
    target->items[0].sellIn = 1;
    target->updateQuality();
    EXPECT_EQ(4, target->items[0].quality);
}

TEST_F(GildedRoseTests, UpdateQualityVoidsBackstagePassQualityWhenSellInLessThan0) {
    target->items[0].name = "Backstage passes to a TAFKAL80ETC concert";
    target->items[0].sellIn = 0;
    target->updateQuality();
    EXPECT_EQ(0, target->items[0].quality);
}

/*TEST_F(GildedRoseTests, UpdateQualityConjuredItemsDegradeTwiceAsFast) {
    target->items[0].name = "Conjured Milk";
    target->items[0].quality = 40;
    target->updateQuality();
    EXPECT_EQ(38, target->items[0].quality);
}*/

