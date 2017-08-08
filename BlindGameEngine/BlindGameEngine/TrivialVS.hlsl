struct Vertex
{
	float4 position : POSITION;
	float4 normal : NORMAL;
	float4 uv : UV;
};

cbuffer WorldViewProj
{
	float4x4 view;
	float4x4 proj;
	float4x4 worldMatrix;
};

struct PixelShaderData
{
	float4 position : SV_POSITION;
	float4 uv : UV;
};

PixelShaderData main(Vertex input)
{
	PixelShaderData result;
	
	result.position = input.position;

	result.position = mul(result.position, worldMatrix);
	result.position = mul(result.position, view);
	result.position = mul(result.position, proj);
	result.uv = input.uv;

	return result;
}