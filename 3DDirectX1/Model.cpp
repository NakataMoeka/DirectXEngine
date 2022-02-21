#include "Model.h"
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

const std::string Model::baseDirectory = "Resources/";
ID3D12Device* Model::dev = nullptr;
UINT Model::descriptorHandleIncrementSize = 0;

void Model::StaticInitialize(ID3D12Device* dev)
{
	
	assert(!Model::dev);

	Model::dev = dev;

	Mesh::StaticInitialize(dev);
}

Model* Model::Create(const std::string& modelname)
{
	Model* instance = new Model;
	instance->Initialize(modelname);

	return instance;
}

Model::~Model()
{
	for (auto m : meshes) {
		delete m;
	}
	meshes.clear();

	for (auto m : materials) {
		delete m.second;
	}
	materials.clear();
}


void Model::Initialize(const std::string& modelname)
{
	HRESULT result = S_FALSE;

	std::ifstream file;
	
	const string filename = modelname + ".obj";
	const string directoryPath = baseDirectory + modelname + "/";
	
	file.open(directoryPath + filename);
	if (file.fail()) {
		assert(0);
	}
	name = modelname;
	//メッシュ
	Mesh* mesh = new Mesh;
	int indexCountTex = 0;

	vector<XMFLOAT3>positions;
	vector<XMFLOAT3>normals;
	vector<XMFLOAT2>texcoords;

	string line;
	while (getline(file, line)) {
		std::istringstream line_stream(line);
		string key;
		getline(line_stream, key, ' ');
		//先頭文字列がvなら頂点座標
		if (key == "mtllib") {
			string filename;
			line_stream >> filename;
			LoadMaterial(directoryPath, filename);
		}
		// 先頭文字列がgならグループの開始
		if (key == "g") {
			//カレントメッシュの情報がそろっているなら
			if (mesh->GetName().size() > 0 && mesh->GetVertexCount() > 0) {
				//コンテナに登録
				meshes.emplace_back(mesh);
				//次のメッシュ生成
				mesh = new Mesh;
				indexCountTex = 0;
			}
			//グループ名読み
			string groupName;
			line_stream >> groupName;
			//メッシュに名前をセット
			mesh->SetName(groupName);
		}
		if (key == "v") {
			//座標読み込み
			XMFLOAT3 position{};
			line_stream >> position.x;
			line_stream >> position.y;
			line_stream >> position.z;
			//座標データに追加
			positions.emplace_back(position);

		}
		if (key == "vt") {
			//UV読み込み
			XMFLOAT2 texcoord{};
			line_stream >> texcoord.x;
			line_stream >> texcoord.y;
			//V方向反転
			texcoord.y = 1.0f - texcoord.y;
			texcoords.emplace_back(texcoord);
		}
		if (key == "vn") {
			XMFLOAT3 normal{};
			line_stream >> normal.x;
			line_stream >> normal.y;
			line_stream >> normal.z;

			normals.emplace_back(normal);
		}
		// 先頭文字列がusemtlならマテリアルを割り当てる
		if (key == "usemtl")
		{
			if (mesh->GetMaterial() == nullptr) {
				//マテリアルの名読み
				string materialName;
				line_stream >> materialName;
				//マテリアル名で検索し、マテリアルを割り当てる
				auto itr = materials.find(materialName);
				if(itr!=materials.end()){
					mesh->SetMaterial(itr->second);
				}
			}
		}
		if (key == "f") {
			int faceIndexCount = 0;

			string index_string;
			while (getline(line_stream, index_string, ' '))
			{
				// 頂点インデックス1個分の文字列をストリームに変換して解析しやすくする
				std::istringstream index_stream(index_string);
				unsigned short indexPosition, indexNormal, indexTexcoord;
				// 頂点番号
				index_stream >> indexPosition;
				Material* material = mesh->GetMaterial();
				index_stream.seekg(1, ios_base::cur);//スラッシュを飛ばす
				//マテリアル、テクスチャがある場合
				if (material && material->textureFilename.size() > 0) {

					index_stream >> indexTexcoord;
					index_stream.seekg(1, ios_base::cur);//スラッシュを飛ばす
					index_stream >> indexNormal;
					//頂点データの追加
					Mesh::VertexPosNormalUv vertex{};
					vertex.pos = positions[indexPosition - 1];
					vertex.normal = normals[indexNormal - 1];
					vertex.uv = texcoords[indexTexcoord - 1];
					mesh->AddVertex(vertex);
				}
				else {
					char c;
					index_stream >> c;
					if (c == '/') {
						//頂点データの追加
						Mesh::VertexPosNormalUv vertex{};
						vertex.pos = positions[indexPosition - 1];
						vertex.normal = {0,0,1};
						vertex.uv = {0,0};
						mesh->AddVertex(vertex);
					}
					else {
						index_stream.seekg(-1, ios_base::cur); // 1文字戻る
						index_stream >> indexTexcoord;
						index_stream.seekg(1, ios_base::cur); // スラッシュを飛ばす
						index_stream >> indexNormal;
						// 頂点データの追加
						Mesh::VertexPosNormalUv vertex{};
						vertex.pos = positions[indexPosition - 1];
						vertex.normal = normals[indexNormal - 1];
						vertex.uv = { 0, 0 };
						mesh->AddVertex(vertex);
					}
				}
				//インデックスデータの追加
				if (faceIndexCount >= 3) {
					//四角形ポリゴンの4点目なので
					//四角形の0,1,2,3の内 2,3,0で三角形を構築する
					mesh->AddIndex(indexCountTex - 1);
					mesh->AddIndex(indexCountTex);
					mesh->AddIndex(indexCountTex - 3);
				 }
				else {
					mesh->AddIndex(indexCountTex);
				}
				indexCountTex++;
				faceIndexCount++;
			}

		}

	}
	file.close();

	//コンテナに登録
	meshes.emplace_back(mesh);

	// メッシュのマテリアルチェック
	for (auto& m : meshes) {
		// マテリアルの割り当てがない
		if (m->GetMaterial() == nullptr) {
			if (defaultMaterial == nullptr) {
				// デフォルトマテリアルを生成
				defaultMaterial = Material::Create();
				defaultMaterial->name = "no material";
				materials.emplace(defaultMaterial->name, defaultMaterial);
			}
			// デフォルトマテリアルをセット
			m->SetMaterial(defaultMaterial);
		}
	}

	// メッシュのバッファ生成
	for (auto& m : meshes) {
		m->CreateBuffers();
	}

	// マテリアルの数値を定数バッファに反映
	for (auto& m : materials) {
		m.second->Update();
	}

	// デスクリプタヒープ生成
	CreateDescriptorHeap();

	// テクスチャの読み込み
	LoadTextures();

}

void Model::LoadTextures()
{
	int textureIndex = 0;
	string directoryPath = baseDirectory + name + "/";

	for (auto& m : materials) {
		Material* material = m.second;

		// テクスチャあり
		if (material->textureFilename.size() > 0) {
			CD3DX12_CPU_DESCRIPTOR_HANDLE cpuDescHandleSRV = CD3DX12_CPU_DESCRIPTOR_HANDLE(descHeap->GetCPUDescriptorHandleForHeapStart(), textureIndex, descriptorHandleIncrementSize);
			CD3DX12_GPU_DESCRIPTOR_HANDLE gpuDescHandleSRV = CD3DX12_GPU_DESCRIPTOR_HANDLE(descHeap->GetGPUDescriptorHandleForHeapStart(), textureIndex, descriptorHandleIncrementSize);
			// マテリアルにテクスチャ読み込み
			material->LoadTexture(directoryPath, cpuDescHandleSRV, gpuDescHandleSRV);
			textureIndex++;
		}
		// テクスチャなし
		else {
			CD3DX12_CPU_DESCRIPTOR_HANDLE cpuDescHandleSRV = CD3DX12_CPU_DESCRIPTOR_HANDLE(descHeap->GetCPUDescriptorHandleForHeapStart(), textureIndex, descriptorHandleIncrementSize);
			CD3DX12_GPU_DESCRIPTOR_HANDLE gpuDescHandleSRV = CD3DX12_GPU_DESCRIPTOR_HANDLE(descHeap->GetGPUDescriptorHandleForHeapStart(), textureIndex, descriptorHandleIncrementSize);
			// マテリアルにテクスチャ読み込み
			material->LoadTexture(baseDirectory, cpuDescHandleSRV, gpuDescHandleSRV);
			textureIndex++;
		}
	}
}


void Model::LoadMaterial(const std::string& directoryPath, const std::string& filename)
{
	//ファイルストリーム
	std::ifstream file;
	//マテリアルファイルを開く
	file.open(directoryPath + filename);
	//ファイルオープン失敗をチェック
	if (file.fail())
	{
		assert(0);
	}
	Material* material = nullptr;
	//1行ずつ読み込む
	string line;
	while (getline(file, line))
	{
		//1行分の文字列をストリームに変換
		std::istringstream line_stream(line);

		//半角スペース区切りで行の先頭文字列を取得
		string key;
		getline(line_stream, key, ' ');

		//先頭のタブ文字は無視する
		if (key[0] == '\t')
		{
			key.erase(key.begin()); //先頭の文字を削除
		}

		//先頭の文字列がnewmtlならマテリアル名
		if (key == "newmtl"){
			//既にマテリアルがあれば
			if (material) {
				//マテリアルをコンテナに登録
				AddMaterial(material);
			}
			//新しいマテリアルを生成
			material = Material::Create();
			//マテリアル名読み込み
			line_stream >> material->name;
		}

		//先頭の文字列がKaならアンビエント色
		if (key == "Ka")
		{
			line_stream >> material->ambient.x;
			line_stream >> material->ambient.y;
			line_stream >> material->ambient.z;
		}

		//先頭の文字列がKdならディフューズ色
		if (key == "Kd")
		{
			line_stream >> material->diffuse.x;
			line_stream >> material->diffuse.y;
			line_stream >> material->diffuse.z;
		}

		//先頭の文字列がKsならスペキュラー色
		if (key == "Ks")
		{
			line_stream >> material->specular.x;
			line_stream >> material->specular.y;
			line_stream >> material->specular.z;
		}

		//先頭の文字列がmap_Kdならテクスチャファイル名
		if (key == "map_Kd")
		{
			//テクスチャのファイル名読み込み
			line_stream >> material->textureFilename;
			// フルパスからファイル名を取り出す
			size_t pos1;
			pos1 = material->textureFilename.rfind('\\');
			if (pos1 != string::npos) {
				material->textureFilename = material->textureFilename.substr(pos1 + 1, material->textureFilename.size() - pos1 - 1);
			}

			pos1 = material->textureFilename.rfind('/');
			if (pos1 != string::npos) {
				material->textureFilename = material->textureFilename.substr(pos1 + 1, material->textureFilename.size() - pos1 - 1);
			}
		}
	}
	//ファイルを閉じる
	file.close();
	if (material) {
		// マテリアルを登録
		AddMaterial(material);
	}
}

void Model::AddMaterial(Material* material)
{
	// コンテナに登録
	materials.emplace(material->name, material);
}

void Model::CreateDescriptorHeap()
{
	HRESULT result = S_FALSE;

	// マテリアルの数
	size_t count = materials.size();

	// デスクリプタヒープを生成	
	if (count > 0) {
		D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc = {};
		descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
		descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;//シェーダから見えるように
		descHeapDesc.NumDescriptors = (UINT)count; // シェーダーリソースビューの数
		result = dev->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(&descHeap));//生成
		if (FAILED(result)) {
			assert(0);
		}
	}

	// デスクリプタサイズを取得
	descriptorHandleIncrementSize = dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

}

void Model::Draw(ID3D12GraphicsCommandList* cmdList)
{	
	// デスクリプタヒープの配列
	if (descHeap) {
		ID3D12DescriptorHeap* ppHeaps[] = { descHeap.Get() };
		cmdList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);
	}

	// 全メッシュを描画
	for (auto& mesh : meshes) {
		mesh->Draw(cmdList);
	}
}

