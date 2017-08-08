struct PixelShaderData
{
	float4 position : SV_POSITION;
	float4 uv: UV;
};

float4 main(PixelShaderData input) : SV_TARGET
{		
	return input.uv;
}