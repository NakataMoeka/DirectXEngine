#include "Mesh.h"
#include <d3dcompiler.h>
#include <cassert>

#pragma comment(lib, "d3dcompiler.lib")

ID3D12Device* Mesh::dev = nullptr;

void Mesh::StaticInitialize(ID3D12Device* dev)
{
	assert(Mesh::dev);
	Mesh::dev = dev;
	Material::StaticInitialize(dev);
}

void Mesh::SetName(const std::string& name)
{
	this->name = name;
}

void Mesh::AddVertex(const VertexPosNormalUv& vertex)
{
	vertices.emplace_back(vertex);
}

void Mesh::AddIndex(unsigned short index)
{
	indices.emplace_back(index);
}

void Mesh::SetMaterial(Material* material)
{
	this->material = material;
}

void Mesh::CreateBuffers()
{
	HRESULT result;
	// ���_�f�[�^�S�̂̃T�C�Y = ���_�f�[�^����̃T�C�Y * ���_�f�[�^�̗v�f��
	UINT sizeVB = static_cast<UINT>(sizeof(VertexPosNormalUv) * vertices.size());

	result = dev->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(sizeVB),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr, IID_PPV_ARGS(&vertBuff)
	);

	// ���_�o�b�t�@�ւ̃f�[�^�]��
	VertexPosNormalUv* vertMap = nullptr;
	result = vertBuff->Map(0, nullptr, (void**)&vertMap);
	if (SUCCEEDED(result)) {
		std::copy(vertices.begin(), vertices.end(), vertMap);
		vertBuff->Unmap(0, nullptr);
	}
	if (FAILED(result)) {
		assert(0);
		return;
	}

	vbView.BufferLocation = vertBuff->GetGPUVirtualAddress();
	vbView.SizeInBytes = sizeVB;
	vbView.StrideInBytes = sizeof(vertices[0]);

	//�C���f�b�N�X�f�[�^�̑S�T�C�Y
	UINT sizeIB = static_cast<UINT>(sizeof(unsigned short) * indices.size());

	result = dev->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(sizeIB),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr, IID_PPV_ARGS(&indexBuff)
	);

	// �C���f�b�N�X�o�b�t�@�ւ̃f�[�^�]��
	unsigned short* indexMap = nullptr;
	result = indexBuff->Map(0, nullptr, (void**)&indexMap);
	if (SUCCEEDED(result)) {
		//�S�C���f�b�N�X�ɑ΂���
		std::copy(indices.begin(), indices.end(), indexMap);
		//�Ȃ��������
		indexBuff->Unmap(0, nullptr);
	}

	// �C���f�b�N�X�o�b�t�@�r���[�̍쐬
	ibView.BufferLocation = indexBuff->GetGPUVirtualAddress();
	ibView.Format = DXGI_FORMAT_R16_UINT;
	ibView.SizeInBytes = sizeIB;
}

void Mesh::Draw(ID3D12GraphicsCommandList* cmdList)
{
	// ���_�o�b�t�@���Z�b�g
	cmdList->IASetVertexBuffers(0, 1, &vbView);
	// �C���f�b�N�X�o�b�t�@���Z�b�g
	cmdList->IASetIndexBuffer(&ibView);
	// �V�F�[�_���\�[�X�r���[���Z�b�g
	cmdList->SetGraphicsRootDescriptorTable(2, material->GetGpuHandle());

	// �}�e���A���̒萔�o�b�t�@���Z�b�g
	ID3D12Resource* constBuff = material->GetConstantBuffer();
	cmdList->SetGraphicsRootConstantBufferView(1, constBuff->GetGPUVirtualAddress());

	// �`��R�}���h
	cmdList->DrawIndexedInstanced((UINT)indices.size(), 1, 0, 0, 0);
}

