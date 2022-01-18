#include "MainShader.hpp"

MainShader::MainShader()
{
	rect = new sf::RectangleShape(sf::Vector2f(50,50));
	rect->setFillColor(sf::Color::White);
	rect->setPosition(sf::Vector2f(78, 800));

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
	fragContent = "#define HAS_COLOR_TRANSFORM \\n" + fragContent;

	if (!s_mainShader->loadFromMemory(vertContent.c_str(), fragContent.c_str()))
	{
		std::cout << "Could not load shaders\n";
		return;
	}

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


void MainShader::render(sf::RenderTarget& target)
{
	s_mainShader->setUniform("col", colorVec);
	s_mainShader->setUniform("colAdd", colAdd);
	s_mainShader->setUniform("colMul", colMul);
	s_mainShader->setUniform("colTrans", colTrans);

	if (s_mainShader)
		target.draw(*rect, s_mainShader);
	else
		target.draw(*rect);
}

void MainShader::im()
{
	ImGui::Begin("Shader Tools");
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
	ImGui::End();
}