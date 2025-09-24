/********************************************************************************
* Copyright (c) 2025 Contributors to the Eclipse Foundation
*
* See the NOTICE file(s) distributed with this work for additional
* information regarding copyright ownership.
*
* This program and the accompanying materials are made available under the
* terms of the Apache License Version 2.0 which is available at
* https://www.apache.org/licenses/LICENSE-2.0
*
* SPDX-License-Identifier: Apache-2.0
********************************************************************************/

#ifndef SRC_DAAL_AF_WORKER_WORKER_THREAD_H_
#define SRC_DAAL_AF_WORKER_WORKER_THREAD_H_
#include <pthread.h>
#include <sched.h>

#include <atomic>
#include <condition_variable>
#include <functional>
#include <future>
#include <memory>
#include <mutex>
#include <queue>

namespace daal {

namespace af {

namespace worker {
/**
 * \class WorkerThread
 * \brief Manages a worker thread that executes a queue of tasks.
 *
 * The WorkerThread class provides functionality to create a thread that can
 * execute a list of tasks with specified core affinity and priority. It
 * ensures proper resource management and thread synchronization.
 *
 * \note
 * - The worker thread runs in a loop, waiting for tasks to be submitted and
 *   executing them.
 * - Proper synchronization is ensured using mutex and condition variable.
 * - The stop_flag_ is used to signal the thread to stop execution.
 */
class WorkerThread {
 public:
  // Default constructor
  WorkerThread() = delete;

  // Copy constructor
  WorkerThread(const WorkerThread &) = default;

  // Copy assignment operator
  WorkerThread &operator=(const WorkerThread &) & = default;

  // Move constructor
  WorkerThread(WorkerThread &&) = default;

  // Move assignment operator
  WorkerThread &operator=(WorkerThread &&) & = default;

  /**
   * \brief Constructs a WorkerThread with specified core ID and priority.
   *
   * \param core_id The ID of the core to which the thread should be affined.
   * \param priority The priority of the thread.
   */
  WorkerThread(unsigned int core_id, int priority);

  /**
   * \brief Destructor for WorkerThread.
   *
   * Ensures the worker thread is properly stopped and resources are cleaned up.
   */
  virtual ~WorkerThread();

  /**
   * \brief Alias for a queue of tasks.
   *
   * Each task is a std::function that returns a boolean indicating success or
   * failure.
   */
  using TaskList = std::queue<std::function<bool()>>;

  /**
   * \brief Submits a list of tasks to the worker thread. If the thread is not
   * free to accept new tasks then Sumbit function will block until worker
   * thread is free.
   *
   * \param new_tasks The list of tasks to be executed.
   * \return A future that will be set with the result of task execution.
   */
  std::future<bool> Submit(TaskList new_tasks);

  /**
   * \brief Submits a list of tasks to the worker thread. If the thread is not
   * free to accept new tasks then Sumbit function will block until worker
   * thread is free.
   *
   * \param task Single tasks to be executed.
   * \return A future that will be set with the result of task execution.
   */
  std::future<bool> Submit(std::function<bool()> task);

  /**
   * \brief Submits a list of tasks to the worker thread. If the thread is not
   * free to accept new tasks then Sumbit function will return immediately.
   *
   * \param new_tasks The list of tasks to be executed.
   * \return A future that will be set with the result of task execution.
   */
  std::future<bool> TrySubmit(TaskList new_tasks);

 private:
  /**
   * \brief Starts the worker thread.
   *
   * This function creates a new thread and starts executing the Run() method.
   */
  void InitializeThreadAttributes(int priority);
  /**   * \brief Entry function for the worker thread.;   *
   * This function is called when the thread is started.
   *
   * \param arg A pointer to the WorkerThread instance.
   * \return A null pointer.
   */
  static void *ThreadEntryFunction(void *arg);
  /**   * \brief Sets the thread affinity to the specified core.
   *
   * \param core_id The ID of the core to which the thread should be affined.
   * \return true if the affinity was successfully set, false otherwise.
   */
  bool SetThreadAffinity(unsigned int core_id);
  /**   * \brief Fulfills the promise with the specified value.
   *
   * \param success The value to fulfill the promise with.
   */
  void FulFillPromise(bool);
  /**   * \brief Main loop for the worker thread.
   *    * This function runs in a loop, waiting for tasks to be submitted and
   * executing them.   */
  void Run();

  pthread_t worker_thread_;
  TaskList tasks_;
  std::mutex mutex_;
  std::condition_variable condition_;
  std::condition_variable submit_condition_;
  std::unique_ptr<std::promise<bool>> worker_promise_;
  std::atomic<bool> stop_flag_;
  pthread_attr_t thread_attr_;
  unsigned int core_id_;
};

}  // namespace worker

}  // namespace af

}  // namespace daal

#endif /* SRC_DAAL_AF_WORKER_WORKER_THREAD_H_ */
