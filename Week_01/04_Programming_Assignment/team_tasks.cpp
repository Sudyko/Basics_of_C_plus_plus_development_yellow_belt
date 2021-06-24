TasksInfo operator+ (TasksInfo rhs, TasksInfo lhs) {
    rhs[TaskStatus::NEW] += lhs[TaskStatus::NEW];
    rhs[TaskStatus::IN_PROGRESS] += lhs[TaskStatus::IN_PROGRESS];
    rhs[TaskStatus::TESTING] += lhs[TaskStatus::TESTING];
    rhs[TaskStatus::DONE] += lhs[TaskStatus::DONE];
    return rhs;
}

void eraseNulls(TasksInfo& tasks) {
    for (auto it = tasks.begin(); it != tasks.end(); ) {
        if (it->second == 0)
            it = tasks.erase(it);
        else
            ++it;
    }
}

class TeamTasks {
public:
    // Получить статистику по статусам задач конкретного разработчика
    const TasksInfo& GetPersonTasksInfo(const string& person) const {
        return users.at(person);
    }

    // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
    void AddNewTask(const string& person) {
        ++users[person][TaskStatus::NEW];
    }

    // Обновить статусы по данному количеству задач конкретного разработчика,
    // подробности см. ниже
    tuple<TasksInfo, TasksInfo> PerformPersonTasks(
        const string& person, int task_count) {
        if (users.find(person) == users.end()) {
            TasksInfo null_ti;
            return make_tuple(null_ti, null_ti);
        } else {
            TasksInfo result_status;
            while (task_count && users[person][TaskStatus::NEW]) {
                ++result_status[TaskStatus::IN_PROGRESS];
                --users[person][TaskStatus::NEW];
                --task_count;
            }
            while (task_count && users[person][TaskStatus::IN_PROGRESS]) {
                ++result_status[TaskStatus::TESTING];
                --users[person][TaskStatus::IN_PROGRESS];
                --task_count;
            }
            while (task_count && users[person][TaskStatus::TESTING]) {
                ++result_status[TaskStatus::DONE];
                --users[person][TaskStatus::TESTING];
                --task_count;
            }
            TasksInfo untouched_tasks = users[person];
            untouched_tasks[TaskStatus::DONE] = 0;
            users[person] = users[person] + result_status;
            eraseNulls(result_status);
            eraseNulls(untouched_tasks);
            eraseNulls(users[person]);
            return make_tuple(result_status, untouched_tasks);
        }
    }
private: 
    map<string, TasksInfo> users;
};