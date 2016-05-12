#ifndef GameScene_hpp
#define GameScene_hpp

class GameScene : public Engine::Scene
{
public:
	GameScene() {};
	~GameScene() {};

	virtual void Init() override {
		cam = new Camera();
		GLAssert();

		EM = Engine::EntityManager::GetInstance();
		SM = Engine::SystemManager::GetInstance();

		SM->AddSystem<Engine::RenderingSystem>(&window);
		GLAssert();

		if (SM->GetSystem<Engine::RenderingSystem>() != nullptr) {
			SM->GetSystem<Engine::RenderingSystem>()->SetCamera(cam);
		}
	};

	virtual void Cleanup() override {};

	virtual void Pause()  override {};
	virtual void Resume()  override {};

	virtual void Update(DeltaTime deltaTime) override {
		EM->Update(deltaTime);
		SM->Update(deltaTime);
	};

private:
	Camera* cam;

	Engine::EntityManager* EM;
	Engine::SystemManager* SM;
};

#endif