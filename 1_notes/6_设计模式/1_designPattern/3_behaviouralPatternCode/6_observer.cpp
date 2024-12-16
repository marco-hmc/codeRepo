#include <iostream>
#include <memory>
#include <string>
#include <vector>

class JobPost {
  public:
    JobPost(const std::string& title) : title_(title) {}

    std::string getTitle() const { return title_; }

  private:
    std::string title_;
};

class Observer {
  public:
    virtual ~Observer() = default;
    virtual void onJobPosted(const std::shared_ptr<JobPost>& job) = 0;
};

class JobSeeker : public Observer {
  public:
    JobSeeker(const std::string& name) : name_(name) {}

    void onJobPosted(const std::shared_ptr<JobPost>& job) override {
        std::cout << "Hi " << name_ << "! New job posted: " << job->getTitle()
                  << std::endl;
    }

  private:
    std::string name_;
};

class Observable {
  public:
    virtual ~Observable() = default;
    virtual void attach(const std::shared_ptr<Observer>& observer) = 0;
    virtual void notify(const std::shared_ptr<JobPost>& jobPosting) = 0;
};

class EmploymentAgency : public Observable {
  public:
    void attach(const std::shared_ptr<Observer>& observer) override {
        observers_.push_back(observer);
    }

    void notify(const std::shared_ptr<JobPost>& jobPosting) override {
        for (const auto& observer : observers_) {
            observer->onJobPosted(jobPosting);
        }
    }

    void addJob(const std::shared_ptr<JobPost>& jobPosting) {
        notify(jobPosting);
    }

  private:
    std::vector<std::shared_ptr<Observer>> observers_;
};

int main() {
    auto johnDoe = std::make_shared<JobSeeker>("John Doe");
    auto janeDoe = std::make_shared<JobSeeker>("Jane Doe");

    auto jobPostings = std::make_shared<EmploymentAgency>();
    jobPostings->attach(johnDoe);
    jobPostings->attach(janeDoe);

    jobPostings->addJob(std::make_shared<JobPost>("Software Engineer"));

    return 0;
}
