#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <windows.h>

using namespace std;

struct Task {
    int id;
    string taskName;
    bool isComplete;
};

class TaskManager {
private:
    vector<Task> taskList;
    int lastAssignedId = 0;

    void printTask() // 打印任务列表
    {
        cout << "当前存在任务为：" << endl;
        for (auto it = taskList.begin(); it != taskList.end();) {
            cout << it->id << " " << it->taskName << " ";
            if (it->isComplete == true) {
                cout << "已完成" << endl;
            } else {
                cout << "未完成" << endl;
            }
            it++;
        }
        cout << endl;
    }

    int readTaskId(const string& prompt) // 键入任务序号处理
    {
        int inputId;
        string input;
        size_t pos;
        while (1) {
            cout << prompt << endl;
            try {
                getline(cin, input);
                inputId = stoi(input, &pos);
            } catch (const invalid_argument& e) {
                cout << "无法转化为整数！请重新输入！" << endl;
                continue;
            } catch (const out_of_range& e) {
                cout << "输入的数超过整数范围！请重新输入！" << endl;
                continue;
            }

            try {
                if (pos < input.size())
                    throw invalid_argument("不能正常转化！请重新输入！");
            } catch (const invalid_argument& e) {
                cout << e.what() << endl;
                continue;
            }
            break;
        }
        return inputId;
    }

    vector<Task>::iterator findTaskById(int id) // 查找所需序号的迭代器
    {
        auto it = taskList.begin();
        while (it != taskList.end()) {
            if (it->id != id) {
                it++;
            } else {
                break;
            }
        }
        return it;
    }
    
    void pauseAndClear()
    {
        getchar();
        system("cls");
    }

public:
    void addTask()
    {
        int flag = 0;
        string title;
        while (flag != 1) {
            cout << "请添加任务于后方：";
            getline(cin, title);
            if (title.size() == 0) {
                cout << "添加失败！任务不能为空！" << endl;
            } else {
                flag = 1;
            }
        }
        taskList.push_back({ ++lastAssignedId, title, false });
        cout << "添加成功！按回车回到主菜单" << endl;
        pauseAndClear();
    }

    void showAllTasks()
    {
        printTask();
        cout << "完成！按回车回到主菜单" << endl;
        pauseAndClear();
    }

    void completeTask()
    {
        printTask();
        int completeId = readTaskId("请输入已经完成的任务序号");
        auto it = findTaskById(completeId);
        if (it == taskList.end()) {
            cout << "输入的序号不存在！按回车回到主菜单。" << endl;
        } else {
            if (it->isComplete) {
                cout << "任务已经完成，无需重复标记！按回车回到主菜单。" << endl;
            } else {
                it->isComplete = true;
                cout << "标记完成成功！按回车回到主菜单。" << endl;
            }
        }
        pauseAndClear();
    }

    void deleteTask()
    {
        printTask();
        int deleteId = readTaskId("请输入即将删除的任务序号");
        auto it = findTaskById(deleteId);
        if (it == taskList.end()) {
            cout << "输入的序号不存在！" << endl;
        } else {
            taskList.erase(it);
            cout << "删除成功！按回车回到主菜单" << endl;
        }
        pauseAndClear();
    }
};

void displayMenu()
{
    cout << "1.添加任务" << endl
         << "2.查看任务" << endl
         << "3.删除任务" << endl
         << "4.完成任务" << endl
         << "0.退出" << endl;
}

int main()
{
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    TaskManager taskManager;
    while (1) {
        displayMenu();
        string choice;
        getline(cin, choice);
        if (choice == "1") {
            taskManager.addTask();
        } else if (choice == "2") {
            taskManager.showAllTasks();
        } else if (choice == "3") {
            taskManager.deleteTask();
        } else if (choice == "4") {
            taskManager.completeTask();
        } else if (choice == "0") {
            return 0;
        }
    }
}