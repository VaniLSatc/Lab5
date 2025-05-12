using System;
using System.Collections.Generic;
using System.Linq;

// Класс для хранения информации о посетителе
public class Visitor
{
    public string Ticket { get; set; }
    public int Duration { get; set; }
}

public class Program
{
    // Функция для генерации номера талона
    private static string GenerateTicket()
    {
        const string charset = "0123456789";
        Random random = new Random();
        string ticket = "T";
        for (int i = 0; i < 3; ++i)
        {
            ticket += charset[random.Next(charset.Length)];
        }
        return ticket;
    }

    // Функция для распределения очереди по окнам
    private static void DistributeVisitors(List<Visitor> queue, int windows)
    {
        if (queue.Count == 0 || windows <= 0) return;

        // Создаем список окон с информацией о времени обработки и списке талонов
        var windowList = new List<Tuple<int, List<string>>>();
        for (int i = 0; i < windows; i++)
        {
            windowList.Add(Tuple.Create(0, new List<string>()));
        }

        // Копируем очередь для сортировки
        var sortedQueue = new List<Visitor>(queue);
        
        // Сортируем по убыванию времени обслуживания
        sortedQueue.Sort((a, b) => b.Duration.CompareTo(a.Duration));

        // Распределяем посетителей по окнам
        foreach (var visitor in sortedQueue)
        {
            // Находим окно с минимальным текущим временем
            var minWindow = windowList.OrderBy(w => w.Item1).First();
            
            // Добавляем посетителя в это окно
            var newTime = minWindow.Item1 + visitor.Duration;
            var newTickets = new List<string>(minWindow.Item2) { visitor.Ticket };
            windowList.Remove(minWindow);
            windowList.Add(Tuple.Create(newTime, newTickets));
        }

        // Выводим результат распределения
        for (int i = 0; i < windows; ++i)
        {
            Console.Write($"Окно {i + 1} ({windowList[i].Item1} минут): ");
            Console.WriteLine(string.Join(", ", windowList[i].Item2));
        }
    }

    public static void Main()
    {
        Random rand = new Random(); // Инициализация генератора случайных чисел

        int windows;
        var queue = new List<Visitor>();

        Console.WriteLine(">>> Введите кол-во окон");
        Console.Write("<<< ");
        windows = int.Parse(Console.ReadLine());

        while (true)
        {
            Console.Write("<<< ");
            string userAnswer = Console.ReadLine();

            if (userAnswer == "ENQUEUE")
            {
                int duration = int.Parse(Console.ReadLine());
                
                Visitor visitor = new Visitor
                {
                    Ticket = GenerateTicket(),
                    Duration = duration
                };
                
                queue.Add(visitor);
                Console.WriteLine($">>> {visitor.Ticket}");
            }
            else if (userAnswer == "DISTRIBUTE")
            {
                DistributeVisitors(queue, windows);
                break;
            }
            else
            {
                Console.WriteLine(">>> Неизвестная команда");
            }
        }
    }
}
