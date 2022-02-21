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
	//���b�V��
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
		//�擪������v�Ȃ璸�_���W
		if (key == "mtllib") {
			string filename;
			line_stream >> filename;
			LoadMaterial(directoryPath, filename);
		}
		// �擪������g�Ȃ�O���[�v�̊J�n
		if (key == "g") {
			//�J�����g���b�V���̏�񂪂�����Ă���Ȃ�
			if (mesh->GetName().size() > 0 && mesh->GetVertexCount() > 0) {
				//�R���e�i�ɓo�^
				meshes.emplace_back(mesh);
				//���̃��b�V������
				mesh = new Mesh;
				indexCountTex = 0;
			}
			//�O���[�v���ǂ�
			string groupName;
			line_stream >> groupName;
			//���b�V���ɖ��O���Z�b�g
			mesh->SetName(groupName);
		}
		if (key == "v") {
			//���W�ǂݍ���
			XMFLOAT3 position{};
			line_stream >> position.x;
			line_stream >> position.y;
			line_stream >> position.z;
			//���W�f�[�^�ɒǉ�
			positions.emplace_back(position);

		}
		if (key == "vt") {
			//UV�ǂݍ���
			XMFLOAT2 texcoord{};
			line_stream >> texcoord.x;
			line_stream >> texcoord.y;
			//V�������]
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
		// �擪������usemtl�Ȃ�}�e���A�������蓖�Ă�
		if (key == "usemtl")
		{
			if (mesh->GetMaterial() == nullptr) {
				//�}�e���A���̖��ǂ�
				string materialName;
				line_stream >> materialName;
				//�}�e���A�����Ō������A�}�e���A�������蓖�Ă�
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
				// ���_�C���f�b�N�X1���̕�������X�g���[���ɕϊ����ĉ�͂��₷������
				std::istringstream index_stream(index_string);
				unsigned short indexPosition, indexNormal, indexTexcoord;
				// ���_�ԍ�
				index_stream >> indexPosition;
				Material* material = mesh->GetMaterial();
				index_stream.seekg(1, ios_base::cur);//�X���b�V�����΂�
				//�}�e���A���A�e�N�X�`��������ꍇ
				if (material && material->textureFilename.size() > 0) {

					index_stream >> indexTexcoord;
					index_stream.seekg(1, ios_base::cur);//�X���b�V�����΂�
					index_stream >> indexNormal;
					//���_�f�[�^�̒ǉ�
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
						//���_�f�[�^�̒ǉ�
						Mesh::VertexPosNormalUv vertex{};
						vertex.pos = positions[indexPosition - 1];
						vertex.normal = {0,0,1};
						vertex.uv = {0,0};
						mesh->AddVertex(vertex);
					}
					else {
						index_stream.seekg(-1, ios_base::cur); // 1�����߂�
						index_stream >> indexTexcoord;
						index_stream.seekg(1, ios_base::cur); // �X���b�V�����΂�
						index_stream >> indexNormal;
						// ���_�f�[�^�̒ǉ�
						Mesh::VertexPosNormalUv vertex{};
						vertex.pos = positions[indexPosition - 1];
						vertex.normal = normals[indexNormal - 1];
						vertex.uv = { 0, 0 };
						mesh->AddVertex(vertex);
					}
				}
				//�C���f�b�N�X�f�[�^�̒ǉ�
				if (faceIndexCount >= 3) {
					//�l�p�`�|���S����4�_�ڂȂ̂�
					//�l�p�`��0,1,2,3�̓� 2,3,0�ŎO�p�`���\�z����
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

	//�R���e�i�ɓo�^
	meshes.emplace_back(mesh);

	// ���b�V���̃}�e���A���`�F�b�N
	for (auto& m : meshes) {
		// �}�e���A���̊��蓖�Ă��Ȃ�
		if (m->GetMaterial() == nullptr) {
			if (defaultMaterial == nullptr) {
				// �f�t�H���g�}�e���A���𐶐�
				defaultMaterial = Material::Create();
				defaultMaterial->name = "no material";
				materials.emplace(defaultMaterial->name, defaultMaterial);
			}
			// �f�t�H���g�}�e���A�����Z�b�g
			m->SetMaterial(defaultMaterial);
		}
	}

	// ���b�V���̃o�b�t�@����
	for (auto& m : meshes) {
		m->CreateBuffers();
	}

	// �}�e���A���̐��l��萔�o�b�t�@�ɔ��f
	for (auto& m : materials) {
		m.second->Update();
	}

	// �f�X�N���v�^�q�[�v����
	CreateDescriptorHeap();

	// �e�N�X�`���̓ǂݍ���
	LoadTextures();

}

void Model::LoadTextures()
{
	int textureIndex = 0;
	string directoryPath = baseDirectory + name + "/";

	for (auto& m : materials) {
		Material* material = m.second;

		// �e�N�X�`������
		if (material->textureFilename.size() > 0) {
			CD3DX12_CPU_DESCRIPTOR_HANDLE cpuDescHandleSRV = CD3DX12_CPU_DESCRIPTOR_HANDLE(descHeap->GetCPUDescriptorHandleForHeapStart(), textureIndex, descriptorHandleIncrementSize);
			CD3DX12_GPU_DESCRIPTOR_HANDLE gpuDescHandleSRV = CD3DX12_GPU_DESCRIPTOR_HANDLE(descHeap->GetGPUDescriptorHandleForHeapStart(), textureIndex, descriptorHandleIncrementSize);
			// �}�e���A���Ƀe�N�X�`���ǂݍ���
			material->LoadTexture(directoryPath, cpuDescHandleSRV, gpuDescHandleSRV);
			textureIndex++;
		}
		// �e�N�X�`���Ȃ�
		else {
			CD3DX12_CPU_DESCRIPTOR_HANDLE cpuDescHandleSRV = CD3DX12_CPU_DESCRIPTOR_HANDLE(descHeap->GetCPUDescriptorHandleForHeapStart(), textureIndex, descriptorHandleIncrementSize);
			CD3DX12_GPU_DESCRIPTOR_HANDLE gpuDescHandleSRV = CD3DX12_GPU_DESCRIPTOR_HANDLE(descHeap->GetGPUDescriptorHandleForHeapStart(), textureIndex, descriptorHandleIncrementSize);
			// �}�e���A���Ƀe�N�X�`���ǂݍ���
			material->LoadTexture(baseDirectory, cpuDescHandleSRV, gpuDescHandleSRV);
			textureIndex++;
		}
	}
}


void Model::LoadMaterial(const std::string& directoryPath, const std::string& filename)
{
	//�t�@�C���X�g���[��
	std::ifstream file;
	//�}�e���A���t�@�C�����J��
	file.open(directoryPath + filename);
	//�t�@�C���I�[�v�����s���`�F�b�N
	if (file.fail())
	{
		assert(0);
	}
	Material* material = nullptr;
	//1�s���ǂݍ���
	string line;
	while (getline(file, line))
	{
		//1�s���̕�������X�g���[���ɕϊ�
		std::istringstream line_stream(line);

		//���p�X�y�[�X��؂�ōs�̐擪��������擾
		string key;
		getline(line_stream, key, ' ');

		//�擪�̃^�u�����͖�������
		if (key[0] == '\t')
		{
			key.erase(key.begin()); //�擪�̕������폜
		}

		//�擪�̕�����newmtl�Ȃ�}�e���A����
		if (key == "newmtl"){
			//���Ƀ}�e���A���������
			if (material) {
				//�}�e���A�����R���e�i�ɓo�^
				AddMaterial(material);
			}
			//�V�����}�e���A���𐶐�
			material = Material::Create();
			//�}�e���A�����ǂݍ���
			line_stream >> material->name;
		}

		//�擪�̕�����Ka�Ȃ�A���r�G���g�F
		if (key == "Ka")
		{
			line_stream >> material->ambient.x;
			line_stream >> material->ambient.y;
			line_stream >> material->ambient.z;
		}

		//�擪�̕�����Kd�Ȃ�f�B�t���[�Y�F
		if (key == "Kd")
		{
			line_stream >> material->diffuse.x;
			line_stream >> material->diffuse.y;
			line_stream >> material->diffuse.z;
		}

		//�擪�̕�����Ks�Ȃ�X�y�L�����[�F
		if (key == "Ks")
		{
			line_stream >> material->specular.x;
			line_stream >> material->specular.y;
			line_stream >> material->specular.z;
		}

		//�擪�̕�����map_Kd�Ȃ�e�N�X�`���t�@�C����
		if (key == "map_Kd")
		{
			//�e�N�X�`���̃t�@�C�����ǂݍ���
			line_stream >> material->textureFilename;
			// �t���p�X����t�@�C���������o��
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
	//�t�@�C�������
	file.close();
	if (material) {
		// �}�e���A����o�^
		AddMaterial(material);
	}
}

void Model::AddMaterial(Material* material)
{
	// �R���e�i�ɓo�^
	materials.emplace(material->name, material);
}

void Model::CreateDescriptorHeap()
{
	HRESULT result = S_FALSE;

	// �}�e���A���̐�
	size_t count = materials.size();

	// �f�X�N���v�^�q�[�v�𐶐�	
	if (count > 0) {
		D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc = {};
		descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
		descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;//�V�F�[�_���猩����悤��
		descHeapDesc.NumDescriptors = (UINT)count; // �V�F�[�_�[���\�[�X�r���[�̐�
		result = dev->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(&descHeap));//����
		if (FAILED(result)) {
			assert(0);
		}
	}

	// �f�X�N���v�^�T�C�Y���擾
	descriptorHandleIncrementSize = dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

}

void Model::Draw(ID3D12GraphicsCommandList* cmdList)
{	
	// �f�X�N���v�^�q�[�v�̔z��
	if (descHeap) {
		ID3D12DescriptorHeap* ppHeaps[] = { descHeap.Get() };
		cmdList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);
	}

	// �S���b�V����`��
	for (auto& mesh : meshes) {
		mesh->Draw(cmdList);
	}
}

