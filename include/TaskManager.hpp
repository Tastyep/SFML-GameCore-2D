#ifndef GAME_CORE_TASK_MANAGER_HPP
#define GAME_CORE_TASK_MANAGER_HPP

#include <atomic>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>

#include <iostream>

namespace GameCore {

class TaskManager {
 public:
  TaskManager() {
    _thread = std::thread([this] { this->processTasks(); });
  }

  template <typename Func>
  void add(Func&& task) {
    {
      std::lock_guard<std::mutex> lock(_mutex);
      _tasks.emplace(task);
    }
    _cv.notify_all();
  }

 private:
  void processTasks() {
    while (!_stopRequested) {
      std::unique_lock<std::mutex> lock(_mutex);
      _cv.wait(lock, [this] { return !_tasks.empty(); });
      _tasks.front()();
      _tasks.pop();
    }
  }

 private:
  std::condition_variable _cv;
  std::mutex _mutex;
  std::thread _thread;
  std::atomic_bool _stopRequested{ false };
  std::queue<std::function<void()>> _tasks;
};

} /* namespace GameCore */

#endif
