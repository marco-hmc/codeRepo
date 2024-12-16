#include <iostream>
#include <memory>

// 前向声明
class MusicPlayer;

// 状态接口
class State {
  public:
    virtual ~State() = default;
    virtual void play(MusicPlayer& player) = 0;
    virtual void pause(MusicPlayer& player) = 0;
    virtual void stop(MusicPlayer& player) = 0;
};

// 播放状态
class PlayingState : public State {
  public:
    void play(MusicPlayer& player) override;
    void pause(MusicPlayer& player) override;
    void stop(MusicPlayer& player) override;
};

// 暂停状态
class PausedState : public State {
  public:
    void play(MusicPlayer& player) override;
    void pause(MusicPlayer& player) override;
    void stop(MusicPlayer& player) override;
};

// 停止状态
class StoppedState : public State {
  public:
    void play(MusicPlayer& player) override;
    void pause(MusicPlayer& player) override;
    void stop(MusicPlayer& player) override;
};

// 音乐播放器类
class MusicPlayer {
  public:
    MusicPlayer() : state_(std::make_unique<StoppedState>()) {}

    void setState(std::unique_ptr<State> state) { state_ = std::move(state); }

    void play() { state_->play(*this); }
    void pause() { state_->pause(*this); }
    void stop() { state_->stop(*this); }

  private:
    std::unique_ptr<State> state_;
};

void PlayingState::play(MusicPlayer& player) { std::cout << "已经在播放中\n"; }

void PlayingState::pause(MusicPlayer& player) {
    std::cout << "暂停播放\n";
    player.setState(std::make_unique<PausedState>());
}

void PlayingState::stop(MusicPlayer& player) {
    std::cout << "停止播放\n";
    player.setState(std::make_unique<StoppedState>());
}

void PausedState::play(MusicPlayer& player) {
    std::cout << "继续播放\n";
    player.setState(std::make_unique<PlayingState>());
}

void PausedState::pause(MusicPlayer& player) { std::cout << "已经暂停\n"; }

void PausedState::stop(MusicPlayer& player) {
    std::cout << "停止播放\n";
    player.setState(std::make_unique<StoppedState>());
}

void StoppedState::play(MusicPlayer& player) {
    std::cout << "开始播放\n";
    player.setState(std::make_unique<PlayingState>());
}

void StoppedState::pause(MusicPlayer& player) {
    std::cout << "已经停止，无法暂停\n";
}

void StoppedState::stop(MusicPlayer& player) { std::cout << "已经停止\n"; }

int main() {
    MusicPlayer player;

    player.play();   // 输出: 开始播放
    player.pause();  // 输出: 暂停播放
    player.play();   // 输出: 继续播放
    player.stop();   // 输出: 停止播放
    player.pause();  // 输出: 已经停止，无法暂停

    return 0;
}
