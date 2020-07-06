#pragma once
#include <D3D11.h>
#include <DirectXMath.h>
#include <stack>
#include <vector>
#include "lsystem.h"
using namespace DirectX;
using namespace std;
class lTree
{
private:
	struct TurtleState
	{
		XMVECTOR pos;
		XMVECTOR dir = XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f);
		XMMATRIX rotation;
	};
	struct VertexType
	{
		VertexType() {};
		VertexType(XMFLOAT3 position) : pos(position) {};
		XMFLOAT3 pos;
		XMFLOAT2 tex;
		XMFLOAT3 normal;
	};
public:
	lTree();
	~lTree();
	bool Initialise(ID3D11Device*, bool);
	bool Render(ID3D11DeviceContext*);
	void interpretRule(std::string, float, float, float);

	void SetWorldMatrix(XMMATRIX);
	XMMATRIX GetWorldMatrix();
	int GetIndexCount();

public:
	TurtleState currentState;
	TurtleState nextState;
	stack<int> indexStack;
	stack<TurtleState> turtleStack;
private:
	
	float angle;
	int size;
	ID3D11Buffer* m_vBuffer, *m_iBuffer;
	vector<VertexType> m_vertices;
	vector<int> m_indices; XMMATRIX m_worldMatrix;
	
};

