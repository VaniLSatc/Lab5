using System;
using System.Collections.Generic;

namespace WarehouseManagement
{
    public class CellContent
    {
        public Dictionary<string, int> Items { get; set; } = new Dictionary<string, int>();
        public int Total { get; set; } = 0;
    }

    class Program
    {
        const int ZONE = 2; // Количество зон хранения
        const int RACK = 6; // Количество стеллажей в каждой зоне
        const int SECTION = 4; // Количество вертикальных секций стеллажа
        const int SHELVE = 4; // Количество полок
        const int MAX_ITEMS = 10; // Максимальное количество товара в ячейке

        static CellContent[,,,] warehouse = new CellContent[ZONE, RACK, SECTION, SHELVE];
        static int totalCapacity = ZONE * RACK * SECTION * SHELVE * MAX_ITEMS;

        static void InitializeWarehouse()
        {
            for (int z = 0; z < ZONE; z++)
                for (int r = 0; r < RACK; r++)
                    for (int s = 0; s < SECTION; s++)
                        for (int sh = 0; sh < SHELVE; sh++)
                            warehouse[z, r, s, sh] = new CellContent();
        }

        static void Add(string address, string item, int count)
        {
            if (count <= 0)
            {
                Console.WriteLine("Количество должно быть положительным.");
                return;
            }

            try
            {
                int zone = address[0] - 'A';
                int rack = int.Parse(address.Substring(1, 2)) - 1;
                int section = address[3] - '0';
                int shelf = address[4] - '0';

                if (zone < 0 || zone >= ZONE || rack < 0 || rack >= RACK || 
                    section < 0 || section >= SECTION || shelf < 0 || shelf >= SHELVE)
                {
                    Console.WriteLine("Некорректный адрес.");
                    return;
                }

                CellContent cell = warehouse[zone, rack, section, shelf];
                
                if (cell.Total + count > MAX_ITEMS)
                {
                    Console.WriteLine("Нельзя добавить товар. Ячейка переполнена.");
                    return;
                }

                if (cell.Items.ContainsKey(item))
                    cell.Items[item] += count;
                else
                    cell.Items.Add(item, count);

                cell.Total += count;
                Console.WriteLine($"Товар '{item}' добавлен.");
            }
            catch (Exception)
            {
                Console.WriteLine("Некорректный адрес.");
            }
        }

        static void Remove(string address, string item, int count)
        {
            if (count <= 0)
            {
                Console.WriteLine("Количество должно быть положительным.");
                return;
            }

            try
            {
                int zone = address[0] - 'A';
                int rack = int.Parse(address.Substring(1, 2)) - 1;
                int section = address[3] - '0';
                int shelf = address[4] - '0';

                if (zone < 0 || zone >= ZONE || rack < 0 || rack >= RACK || 
                    section < 0 || section >= SECTION || shelf < 0 || shelf >= SHELVE)
                {
                    Console.WriteLine("Некорректный адрес.");
                    return;
                }

                CellContent cell = warehouse[zone, rack, section, shelf];
                
                if (!cell.Items.ContainsKey(item) || cell.Items[item] < count)
                {
                    Console.WriteLine($"Недостаточно товара '{item}' для удаления.");
                    return;
                }

                cell.Items[item] -= count;
                cell.Total -= count;
                
                if (cell.Items[item] == 0)
                    cell.Items.Remove(item);
                
                Console.WriteLine($"Товар '{item}' удален.");
            }
            catch (Exception)
            {
                Console.WriteLine("Некорректный адрес.");
            }
        }

        static void Info()
        {
            int totalItems = 0;
            int[] zoneItems = new int[ZONE];
            
            for (int z = 0; z < ZONE; z++)
                for (int r = 0; r < RACK; r++)
                    for (int s = 0; s < SECTION; s++)
                        for (int sh = 0; sh < SHELVE; sh++)
                        {
                            totalItems += warehouse[z, r, s, sh].Total;
                            zoneItems[z] += warehouse[z, r, s, sh].Total;
                        }

            double totalPercent = ((double)totalItems / totalCapacity) * 100;
            Console.WriteLine($"Общая загруженность склада: {totalPercent:F2}%");
            
            for (int z = 0; z < ZONE; z++)
            {
                double zonePercent = ((double)zoneItems[z] / (RACK * SECTION * SHELVE * MAX_ITEMS)) * 100;
                Console.WriteLine($"Зона {(char)('A' + z)}: {zonePercent:F2}%");
            }

            Console.WriteLine("Содержимое ячеек:");
            for (int z = 0; z < ZONE; z++)
                for (int r = 0; r < RACK; r++)
                    for (int s = 0; s < SECTION; s++)
                        for (int sh = 0; sh < SHELVE; sh++)
                        {
                            CellContent cell = warehouse[z, r, s, sh];
                            if (cell.Total > 0)
                            {
                                Console.Write($"{(char)('A' + z)}{r + 1:D2}{s}{sh}: ");
                                Console.Write($"Всего {cell.Total} единиц (");
                                
                                foreach (var kvp in cell.Items)
                                    Console.Write($"{kvp.Key} - {kvp.Value}, ");
                                
                                if (cell.Items.Count > 0)
                                    Console.Write("\b\b");
                                
                                Console.WriteLine(")");
                            }
                        }

            Console.WriteLine("Пустые ячейки:");
            for (int z = 0; z < ZONE; z++)
                for (int r = 0; r < RACK; r++)
                    for (int s = 0; s < SECTION; s++)
                        for (int sh = 0; sh < SHELVE; sh++)
                            if (warehouse[z, r, s, sh].Total == 0)
                                Console.WriteLine($"{(char)('A' + z)}{r + 1:D2}{s}{sh}");
        }

        static void Main(string[] args)
        {
            Console.OutputEncoding = System.Text.Encoding.UTF8;
            InitializeWarehouse();
            
            while (true)
            {
                Console.Write("Введите команду (ADD, REMOVE, INFO, EXIT): ");
                string userAnswer = Console.ReadLine().ToUpper();

                switch (userAnswer)
                {
                    case "ADD":
                        Console.Write("Введите адрес ячейки: ");
                        string addAddress = Console.ReadLine();
                        Console.Write("Введите наименование товара: ");
                        string addItem = Console.ReadLine();
                        Console.Write("Введите количество товара: ");
                        if (int.TryParse(Console.ReadLine(), out int addCount))
                            Add(addAddress, addItem, addCount);
                        else
                            Console.WriteLine("Некорректное количество.");
                        break;
                        
                    case "REMOVE":
                        Console.Write("Введите адрес ячейки: ");
                        string removeAddress = Console.ReadLine();
                        Console.Write("Введите наименование товара: ");
                        string removeItem = Console.ReadLine();
                        Console.Write("Введите количество товара: ");
                        if (int.TryParse(Console.ReadLine(), out int removeCount))
                            Remove(removeAddress, removeItem, removeCount);
                        else
                            Console.WriteLine("Некорректное количество.");
                        break;
                        
                    case "INFO":
                        Info();
                        break;
                        
                    case "EXIT":
                        return;
                        
                    default:
                        Console.WriteLine("Неизвестная команда.");
                        break;
                }
            }
        }
    }
}
