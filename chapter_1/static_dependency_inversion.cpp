// Example for static dependency inversion page 25

#include <iostream>
#include <memory>
#include <utility>
#include <variant>
#include <vector>

class FrontEndDeveloper {
public:
  void develop() { developFrontEnd(); }

private:
  void developFrontEnd() { std::cout << "developFrontEnd" << std::endl; }
};

class BackEndDeveloper {
public:
  void develop() { developBackEnd(); }

private:
  void developBackEnd() { std::cout << "developBackEnd" << std::endl; }
};

template <typename... Devs> class Project {
public:
  using Developers = std::vector<std::variant<Devs...>>;

  explicit Project(Developers developers)
      : developers_(std::move(developers)) {}

  void develop() {
    for (auto &developer : developers_) {
      std::visit([](auto &dev) { dev.develop(); }, developer);
    }
  }

  // private:
  Developers developers_;
};

int main(int argc, char const *argv[]) {
  using MyProject = Project<FrontEndDeveloper, BackEndDeveloper>;
  auto alice = FrontEndDeveloper();
  auto jonny = BackEndDeveloper();

  auto new_project = MyProject{{alice, jonny}};
  new_project.develop();
  new_project.developers_;

  return 0;
}
