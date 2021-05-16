using System;
using System.Collections.Generic;

namespace CSharp
{
    enum ItemType
    {
        Weapon,
        Armor,
        Amulet,
        Ring
    }

    enum Rarity
    {
        Normal,
        Uncommon,
        Rare,
    }

    class Item
    {
        public ItemType ItemType;
        public Rarity Rarity;
    }

    class Program
    {
        static List<Item> _items = new List<Item>();

        static Item FindWeapon()
        {
            foreach (Item item in _items)
            {
                if (item.ItemType == ItemType.Weapon)
                    return item;

            }
            return null;
        }
        

        
        static void Main(string[] args)
        {
            // Lambda : 일회용 함수를 만드는데 사용하는 문법이다. 

            _items.Add(new Item() { ItemType = ItemType.Weapon, Rarity = Rarity.Normal });
            _items.Add(new Item() { ItemType = ItemType.Armor, Rarity = Rarity.Uncommon });
            _items.Add(new Item() { ItemType = ItemType.Ring, Rarity = Rarity.Rare });
            

        }

    }
}

     