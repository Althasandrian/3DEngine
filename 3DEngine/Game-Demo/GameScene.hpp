#ifndef GameScene_hpp
#define GameScene_hpp

class GameScene : public Engine::Scene
{
public:
	GameScene() {};
	~GameScene() {};

	virtual void Init() override {
		_cam = new Camera();

		EM = Engine::EntityManager::GetInstance();
		SM = Engine::SystemManager::GetInstance();

		SM->AddSystem<Engine::RenderingSystem>(&window);

		if (SM->GetSystem<Engine::RenderingSystem>() != nullptr) {
			SM->GetSystem<Engine::RenderingSystem>()->SetCamera(_cam);
		}

		Resource* Skybox = ResourceManager::GetInstance()->LoadResource("Resources/Models/Skybox.obj");
		Resource* playerModel = ResourceManager::GetInstance()->LoadResource("Resources/Models/Player.obj");

		EM->AddEntity("Skybox", std::make_shared<Engine::Entity>());
		EM->AddComponent<Engine::Transform>("Skybox", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(225.0f, 0.0f, -90.0f), glm::vec3(1.0f, 1.0f, 1.0f));
		EM->AddComponent<Engine::Render>("Skybox", Skybox->_vertices, Skybox->_indices);
		EM->AddComponent<Engine::Texture>("Skybox", "Resources/Textures/Skybox.png");
		EM->AddComponent<Engine::Shader>("Skybox", "Resources/Shaders/SkyboxVert.txt", "Resources/Shaders/SkyboxFrag.txt");

		_player = EM->AddEntity("Player", std::make_shared<Engine::Entity>());
		EM->AddComponent<Engine::Transform>("Player", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
		EM->AddComponent<Engine::Render>("Player", playerModel->_vertices, playerModel->_indices);
		EM->AddComponent<Engine::Texture>("Player", "Resources/Textures/Skybox.png");
		EM->AddComponent<Engine::Shader>("Player", "Resources/Shaders/MainMenuVert.txt", "Resources/Shaders/MainMenuFrag.txt");

		_playerTransform = _player->GetComponent<Engine::Transform>();

		window.ConfineMouse();

		window.SetMousePosition(window.GetSize() / 2.0f);

		window.HideCursor(true);
	};

	virtual void Cleanup() override {};

	virtual void Pause()  override {};
	virtual void Resume()  override {};

	virtual void Update(DeltaTime deltaTime) override {
		glm::vec2 MousePos = window.SetMousePosition(window.GetSize() / 2.0f);

		_cam->ProcessMouseMovement(MousePos.x, MousePos.y, GL_TRUE);

		Inputs::Input* inp = nullptr;

		if (inp->getKeyDown('W')) { _cam->ProcessKeyboard(FORWARD, deltaTime); }
		if (inp->getKeyDown('S')) { _cam->ProcessKeyboard(FORWARD, -deltaTime); }
		if (inp->getKeyDown('D')) { _cam->ProcessKeyboard(RIGHT, deltaTime); }
		if (inp->getKeyDown('A')) { _cam->ProcessKeyboard(RIGHT, -deltaTime); }

		_playerTransform->SetPosition(_cam->Position - glm::vec3(0.0f, 1.0f, 0.0f));
		_playerTransform->SetRotation(_cam->Front);

		EM->Update(deltaTime);
		SM->Update(deltaTime);
	};

private:
	Camera* _cam;

	std::shared_ptr<Engine::Entity> _player;
	std::shared_ptr<Engine::Transform> _playerTransform;

	Engine::EntityManager* EM;
	Engine::SystemManager* SM;
};

#endif