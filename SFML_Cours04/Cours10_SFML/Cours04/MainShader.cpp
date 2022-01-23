#include "MainShader.hpp"

MainShader::MainShader()
{
	/*
	rect = new sf::RectangleShape(sf::Vector2f(50,50));
	rect->setFillColor(sf::Color::White);
	rect->setPosition(sf::Vector2f(78, 800));
	*/
	spr = new sf::Sprite();

	texture = new sf::Texture();
	texture->loadFromFile("Assets/Graphs/axoloto.png");
	spr->setTexture(*texture);

	s_mainShader = new sf::Shader();

	std::string vertContent;
	std::string fragContent;
	bool vertOk = loadFromFile(vertexPath, vertContent);
	bool fragOk = loadFromFile(fragPath, fragContent);


	if (!vertOk)
	{
		std::cout << "cannot load vert\n";
		return;
	}
	if (!fragOk)
	{
		std::cout << "cannot load frag\n";
		return;
	}

	//fragContent = "#define HAS_UNIFORM_COLOR \\n" + fragContent;
	fragContent = "#define HAS_TEXTURE \\n" + fragContent;

	if (!s_mainShader->loadFromMemory(vertContent.c_str(), fragContent.c_str()))
	{
		std::cout << "Could not load shaders\n";
		return;
	}

	s_reload.eval();

}

MainShader::~MainShader()
{
	delete (s_mainShader);
	delete (rect);
}

bool MainShader::loadFromFile(const char* path, std::string& res)
{
	FILE* f = 0;
	fopen_s(&f,path, "r");
	if (!f) 
		return false;
	fseek(f, 0L, SEEK_END);
	size_t sz = ftell(f);
	res.resize(sz);
	fseek(f, 0L, SEEK_SET);
	size_t read = fread(res.data(), sz, 1, f);
	if (f)
		fclose(f);
	else
		return false;
	return true;
}


void MainShader::update(float dt)
{
	sTime += dt * sTimeDirection * sTimeSpeed;
	if (sTime > sTimeRange || sTime < -sTimeRange)
		sTimeDirection *= -1;
	
	float dispX = sin(imMovement.x + dt) * imMovementSpeed;
	float dispY = cos(imMovement.y + dt) * imMovementSpeed;

	clamp(dispX, -dispClamp.x, dispClamp.x);
	clamp(dispY, -dispClamp.y, dispClamp.y);

	imMovement = { imMovement.x + dispX, imMovement.y +dispY };

	s_mainShader->setUniform("vert_time", dt * 100);

	s_reload.update(dt);

}

void MainShader::render(sf::RenderTarget& target)
{
	s_mainShader->setUniform("col", colorVec);
	s_mainShader->setUniform("colAdd", colAdd);
	s_mainShader->setUniform("colMul", colMul);
	s_mainShader->setUniform("colTrans", colTrans);
	s_mainShader->setUniform("u_time", sTime);
	s_mainShader->setUniform("movement", imMovement);
	s_mainShader->setUniform("movement_speed", imMovementSpeed);
	s_mainShader->setUniform("blurFactor", imBlur);

	if (s_mainShader)
		target.draw(*spr, s_mainShader);
	else
		target.draw(*spr);
}

void MainShader::clamp(float& f, float min, float max)
{
	if (f > max)
		f = max;
	if (f < min)
		f = min;
}

void MainShader::im()
{
	ImGui::Begin("Shader Tools");
	if (ImGui::TreeNode("Colors"))
	{
		ImGui::DragFloat("sTimeSpeed", &sTimeSpeed, 0.5f, 0, 10);
		if (ImGui::ColorEdit4("colAdd", imColAdd))
		{
			colAdd.x = imColAdd[0];
			colAdd.y = imColAdd[1];
			colAdd.z = imColAdd[2];
			colAdd.w = imColAdd[3];
		}
		if (ImGui::ColorEdit4("colMul", imColMul))
		{
			colMul.x = imColMul[0];
			colMul.y = imColMul[1];
			colMul.z = imColMul[2];
			colMul.w = imColMul[3];
		}
		if (ImGui::TreeNode("colTrans"))
		{
			// je suis sûr qu'il y a plus propre pour faire ça
			if (ImGui::ColorEdit4("r", imColTransR))
				for (int i = 0; i < 4; i++)
					colTrans.array[i] = imColTransR[i];

			if (ImGui::ColorEdit4("g", imColTransG))
				for (int i = 0; i < 4; i++)
					colTrans.array[i] = imColTransG[i];

			if (ImGui::ColorEdit4("b", imColTransB))
				for (int i = 0; i < 4; i++)
					colTrans.array[i] = imColTransB[i];

			if (ImGui::ColorEdit4("a", imColTransA))
				for (int i = 0; i < 4; i++)
					colTrans.array[i] = imColTransA[i];
			ImGui::TreePop();
		}
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("Position"))
	{
		ImGui::DragFloat("mov x", &imMovement.x, 2, -10000, 10000);
		ImGui::DragFloat("mov y", &imMovement.y, 2, -10000, 10000);
		ImGui::DragFloat("mov speed", &imMovementSpeed, 1, 0, 100);
		ImGui::TreePop();
	}
	if (ImGui::DragFloat("displacement", &imDisplacement, 0.05f, -1, 1))
	{
		s_mainShader->setUniform("displacement", imDisplacement);
	}
	(ImGui::DragFloat("blur X", &imBlur.x, 0.05f, -1, 1));
	(ImGui::DragFloat("blur Y", &imBlur.y, 0.05f, -1, 1));

	ImGui::End();
}