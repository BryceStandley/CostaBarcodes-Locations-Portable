#include "Walnut/Application.h"
#include "Walnut/EntryPoint.h"
#include "VERSION.hpp"
#include "Log.h"
#include <iostream>
#include <backends/imgui_impl_vulkan.h>

#include "Config/ConfigurationManager.h"
#include "Locations/Location.h"
#include "Locations/LocationManager.h"
#include "Walnut/Image.h"
#include "Walnut/Random.h"

#include <BitMatrix.h>
#include <MultiFormatWriter.h>


class MainLayer : public Walnut::Layer
{
public:
	Walnut::Image test = Walnut::Image(100, 50, Walnut::ImageFormat::RGBA);
	uint32_t* data;
	MainLayer() : Layer()
	{
		setData();
	}

	void setData()
	{
		ZXing::MultiFormatWriter d(ZXing::BarcodeFormat::QRCode);

		ZXing::BitMatrix t = d.encode("AB0111", 100, 50);

		ZXing::Matrix<uint32_t> tt = ZXing::ToMatrix<uint32_t>(t);
		
		data = (uint32_t*)malloc(sizeof(Walnut::ImageFormat::RGBA) * test.GetWidth() * test.GetHeight());

		for(int x = 0; x < test.GetWidth(); x++)
		{
			for(int y = 0; y < test.GetHeight(); y++)
			{
				data[y * test.GetWidth() + x] = tt.data()[y * test.GetWidth() + x] > 0 ? 0x00000000 : 0x000000FF;
			}
		}

		test.SetData(data);
	}
	
	virtual void OnUIRender() override
	{
		ImGuiWindowFlags window_flags = 0;
		window_flags |= ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		auto size = ImGui::GetMainViewport()->WorkSize;
		auto center = ImGui::GetMainViewport()->GetWorkCenter();
		center.y += 14;
		size.y -= 28;
		ImGui::SetNextWindowPos({center.x, center.y}, ImGuiCond_None, {0.5f, 0.5f});
		ImGui::SetNextWindowSize(size);
		if(ImGui::Begin("Content", nullptr, window_flags))
		{
			if(ImGui::BeginTabBar("TabBar"))
			{
				//Step 0 - Setup and settings
				if(ImGui::BeginTabItem("Step 0"))
				{
					ImGui::Text("Step 0");
					
					if(ImGui::Button("Click me to Test Image gen"))
					{
						free(data);

						setData();
					}
					
					ImGui::Image(test.GetDescriptorSet(), {(float)test.GetWidth(), (float)test.GetHeight()});
					
					ImGui::EndTabItem();
				}

				//Step 1 - Generate location images
				if(ImGui::BeginTabItem("Step 1"))
				{
					ImGui::Text("Step 1");
					ImGui::EndTabItem();
				}

				//Step 2 - Select Locations to Use
				if(ImGui::BeginTabItem("Step 2"))
				{
					ImGui::Text("Step 2");
					ImGui::EndTabItem();
				}

				//Step 3 - Process into PDF
				if(ImGui::BeginTabItem("Step 3"))
				{
					ImGui::Text("Step 3");
					ImGui::EndTabItem();
				}

				//Step 4 - Print? Profit?
				if(ImGui::BeginTabItem("Step 4"))
				{
					ImGui::Text("Step 4");
					ImGui::EndTabItem();
				}
				ImGui::EndTabBar();
			}
			ImGui::End();
		}
	}
};

Walnut::Application* Walnut::CreateApplication(int argc, char** argv)
{
	Walnut::ApplicationSpecification spec;
	spec.Name = "Costa Barcodes Locations - Portable Version: " CB_VERSION;
	spec.Width = 800;
	spec.Height = 600;

	Walnut::Application* app = new Walnut::Application(spec);

	const auto io = &ImGui::GetIO();
	io->IniFilename = nullptr;
	io->LogFilename = nullptr;

	if(ConfigurationManager::Get().IsReady())
	{
		LocationManager::Get().Init(ConfigurationManager::Get().GetConfig().GetLocationStorePath());
	}
	
	app->PushLayer<MainLayer>();
	app->SetMenubarCallback([app]()
	{
		if (ImGui::MenuItem("Exit"))
		{
			app->Close();
		}
		if(ImGui::MenuItem("Help"))
		{
			std::cout << "Help Wanted!" << std::endl;
		}
		if(ImGui::MenuItem("Location Editor"))
		{
			std::cout << "Locations Wanted!" << std::endl;
		}
	});
	return app;
}