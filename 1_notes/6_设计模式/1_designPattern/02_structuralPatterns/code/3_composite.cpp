#include <iostream>
#include <memory>
#include <vector>

// 员工基类
class Employee {
  public:
    Employee(const std::string& name, float salary)
        : name_(name), salary_(salary) {}
    virtual ~Employee() = default;

    virtual float getSalary() const { return salary_; }

  protected:
    std::string name_;
    float salary_;
};

// 开发者类
class Developer : public Employee {
  public:
    Developer(const std::string& name, float salary) : Employee(name, salary) {}
};

// 设计师类
class Designer : public Employee {
  public:
    Designer(const std::string& name, float salary) : Employee(name, salary) {}
};

// 组织类
class Organization {
  public:
    void addEmployee(std::shared_ptr<Employee> employee) {
        employees_.push_back(employee);
    }

    float getNetSalaries() const {
        float netSalary = 0;

        for (const auto& employee : employees_) {
            netSalary += employee->getSalary();
        }

        return netSalary;
    }

  private:
    std::vector<std::shared_ptr<Employee>> employees_;
};

int main() {
    // 准备员工
    auto john = std::make_shared<Developer>("John Doe", 12000);
    auto jane = std::make_shared<Designer>("Jane Doe", 15000);

    // 将他们添加到组织中
    Organization organization;
    organization.addEmployee(john);
    organization.addEmployee(jane);

    // 输出净工资
    std::cout << "净工资: " << organization.getNetSalaries()
              << std::endl;  // 输出: 净工资: 27000

    return 0;
}
