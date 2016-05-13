#ifndef SplashScreenScene_hpp
#define SplashScreenScene_hpp

class SplashScreenScene : public Engine::Scene
{
public:
	SplashScreenScene() {};
	virtual ~SplashScreenScene() {};

	virtual void Init()  override {
		cam = new Camera();

		EM = Engine::EntityManager::GetInstance();
		SM = Engine::SystemManager::GetInstance();

		SM->AddSystem<Engine::RenderingSystem>(&window);

		if (SM->GetSystem<Engine::RenderingSystem>() != nullptr) {
			SM->GetSystem<Engine::RenderingSystem>()->SetCamera(cam);
		}

		Resource* audiores = ResourceManager::GetInstance()->LoadResource("Resources/bossMusic.wav");

		splash = std::dynamic_pointer_cast<Engine::Rectangle>(EM->AddEntity("SplashScreen", std::make_shared<Engine::Rectangle>(glm::vec2(0.0f, 0.0f), glm::vec2(5.0f, 10.0f), -6.0f)));

		EM->AddComponent<Engine::Texture>("SplashScreen", "Resources/SplashScreen.png");
		EM->AddComponent<Engine::Shader>("SplashScreen", "Resources/SplashScreenVertexShader.txt", "Resources/SplashScreenFragmentShader.txt");

		timer = 5;
	};

	virtual void Cleanup()  override {
		EM->Clear();
		SM->Clear();
	};

	virtual void Pause()  override {};

	virtual void Resume()  override {};

	virtual void Update(DeltaTime deltaTime)  override {

		////RGBA8 2D texture, 24 bit depth texture, 256x256
		//GLuint color_tex;
		//glGenTextures(1, &color_tex);
		//glBindTexture(GL_TEXTURE_2D, color_tex);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		////NULL means reserve texture memory, but texels are undefined
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 256, 256, 0, GL_BGRA, GL_UNSIGNED_BYTE, NULL);
		////-------------------------
		//GLuint fb;
		//glGenFramebuffersEXT(1, &fb);
		//glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fb);
		////Attach 2D texture to this FBO
		//glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, color_tex, 0);
		////-------------------------
		//GLuint depth_rb;
		//glGenRenderbuffersEXT(1, &depth_rb);
		//glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, depth_rb);
		//glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT24, 256, 256);
		////-------------------------
		////Attach depth buffer to FBO
		//glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, depth_rb);
		////-------------------------
		////Does the GPU support current FBO configuration?
		//GLenum status;
		//status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
		////switch (status)
		////{
		////case GL_FRAMEBUFFER_COMPLETE_EXT:
		////	cout << "good";
		////default:
		////	HANDLE_THE_ERROR;
		////}
		////-------------------------
		////and now you can render to GL_TEXTURE_2D
		//glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fb);
		//glClearColor(0.0, 0.0, 0.0, 0.0);
		//glClearDepth(1.0f);
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		////-------------------------
		//glViewport(0, 0, 256, 256);
		//glMatrixMode(GL_PROJECTION);
		//glLoadIdentity();
		//glOrtho(0.0, 256.0, 0.0, 256.0, -1.0, 1.0);
		//glMatrixMode(GL_MODELVIEW);
		//glLoadIdentity();
		////-------------------------
		//glDisable(GL_TEXTURE_2D);
		//glDisable(GL_BLEND);
		//glEnable(GL_DEPTH_TEST);
		////-------------------------
		////**************************
		////RenderATriangle, {0.0, 0.0}, {256.0, 0.0}, {256.0, 256.0}
		////Read http://www.opengl.org/wiki/VBO_-_just_examples
		////RenderATriangle();
		////-------------------------
		//GLubyte pixels[4 * 4 * 4];
		//glReadPixels(0, 0, 4, 4, GL_BGRA, GL_UNSIGNED_BYTE, pixels);
		////pixels 0, 1, 2 should be white
		////pixel 4 should be black
		////----------------
		////Bind 0, which means render to back buffer
		//glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

		EM->Update(deltaTime);
		SM->Update(deltaTime);

		timer -= deltaTime;

		//if (splash->PointIntersect(&window, cam, window.GetCursorPosition())) {
		//	std::cout << "asd" << std::endl;
		//}

		if (timer < 0) {
			//Delete resources
//			glDeleteTextures(1, &color_tex);
//			glDeleteRenderbuffersEXT(1, &depth_rb);
			//Bind 0, which means render to back buffer, as a result, fb is unbound
//			glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
//			glDeleteFramebuffersEXT(1, &fb);


			Engine::SceneManager::GetInstance()->ChangeScene(new MainMenuScene());
		}
	};

private:
	std::shared_ptr<Engine::Rectangle> splash;

	DeltaTime timer;

	Camera* cam;

	Engine::EntityManager* EM;
	Engine::SystemManager* SM;
};

#endif