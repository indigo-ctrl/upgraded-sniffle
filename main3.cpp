#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

struct Client {
    int id;
    int arrival_time;
    int service_time;
};

struct Window {
    int id;
    int free_at_time;
    
    // Для priority_queue (минимальное время освобождения в начале)
    bool operator>(const Window& other) const {
        return free_at_time > other.free_at_time;
    }
};

void simulateBank(int num_windows, int num_clients) {
    // Очередь клиентов
    std::queue<Client> client_queue;
    
    // Приоритетная очередь для окон (самое раннее освобождение)
    std::priority_queue<Window, std::vector<Window>, std::greater<Window>> windows;
    
    // Инициализация окон (все свободны в момент времени 0)
    for (int i = 0; i < num_windows; ++i) {
        windows.push({i, 0});
    }
    
    // Генерация клиентов (для примера - случайные данные)
    std::vector<Client> clients;
    for (int i = 0; i < num_clients; ++i) {
        int arrival = i * 2;  // Клиенты приходят каждые 2 минуты
        int service = rand() % 5 + 1;  // Время обслуживания 1-5 минут
        clients.push_back({i, arrival, service});
    }
    
    // Статистика
    double total_wait_time = 0;
    int max_queue_length = 0;
    std::vector<int> window_busy_time(num_windows, 0);
    int current_time = 0;
    size_t client_index = 0;
    
    // Основной цикл симуляции
    while (client_index < clients.size() || !client_queue.empty()) {
        // Добавляем новых клиентов в очередь
        while (client_index < clients.size() && clients[client_index].arrival_time <= current_time) {
            client_queue.push(clients[client_index]);
            client_index++;
        }
        
        // Обновляем максимальную длину очереди
        max_queue_length = std::max(max_queue_length, (int)client_queue.size());
        
        // Обслуживаем клиентов в свободных окнах
        while (!windows.empty() && windows.top().free_at_time <= current_time && !client_queue.empty()) {
            Window current_window = windows.top();
            windows.pop();
            
            Client current_client = client_queue.front();
            client_queue.pop();
            
            // Время ожидания клиента
            int wait_time = current_time - current_client.arrival_time;
            total_wait_time += wait_time;
            
            // Обновляем время занятости окна
            window_busy_time[current_window.id] += current_client.service_time;
            
            // Окно освободится через время обслуживания
            current_window.free_at_time = current_time + current_client.service_time;
            windows.push(current_window);
        }
        
        // Переходим к следующему событию
        if (!windows.empty()) {
            current_time = windows.top().free_at_time;
        } else if (client_index < clients.size()) {
            current_time = clients[client_index].arrival_time;
        }
    }
    
    // Вывод результатов
    std::cout << "=== Результаты симуляции ===" << std::endl;
    std::cout << "Среднее время ожидания: " << total_wait_time / num_clients << " минут" << std::endl;
    std::cout << "Максимальная длина очереди: " << max_queue_length << std::endl;
    
    std::cout << "Загрузка окон:" << std::endl;
    int total_time = current_time;
    for (int i = 0; i < num_windows; ++i) {
        double load = (double)window_busy_time[i] / total_time * 100;
        std::cout << "  Окно " << i << ": " << load << "%" << std::endl;
    }
}

int main() {
    // Пример: 3 окна, 20 клиентов
    simulateBank(3, 20);
    
    return 0;
}