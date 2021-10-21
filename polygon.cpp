//=============================================================================
//
// �|���S���\������ [polygon.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "camera.h"
#include "polygon.h"
#include "texture.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_MAX		(1)							// �e�N�X�`���̐�

#define	VALUE_MOVE		(5.0f)						// �ړ���
#define	VALUE_ROTATE	(D3DX_PI * 0.02f)			// ��]��

#define	SIZE_X			(100.0f)					// �n�ʂ̃T�C�Y(X����)
#define SIZE_Y          (100.0f)
#define	SIZE_Z			(100.0f)					// �n�ʂ̃T�C�Y(Z����)
#define VERTEX_NUM		(36)

#define DICE_HEIGHT (FLOAT)(1.0f / 3.0f )
#define DICE_WIDHT  (FLOAT)(1.0f / 4.0f )

#define H2 DICE_HEIGHT * 2.0f
#define H3 DICE_HEIGHT * 3.0f

#define W2 DICE_WIDHT * 2.0f
#define W3 DICE_WIDHT * 3.0f
#define W4 DICE_WIDHT * 4.0f


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexPolygon(void);


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11Buffer					*g_VertexBuffer = NULL;	// ���_���

static POLYGON						g_Polygon;			// �|���S���f�[�^
static int							g_TexNo;			// �e�N�X�`���ԍ�


// ���_�z��
static VERTEX_3D g_VertexArray[VERTEX_NUM] = {
	//���ꂪ���[�J�����W�n
	//�|�W�V����,�@��,�f�B�t���[�Y,���_���W

	//��
	/*{D3DXVECTOR3(-SIZE_X, SIZE_Y,  SIZE_Z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f)},
	{D3DXVECTOR3( SIZE_X, SIZE_Y,  SIZE_Z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f)},
	{D3DXVECTOR3(-SIZE_X, SIZE_Y, -SIZE_Z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f)},
	{D3DXVECTOR3(SIZE_X, SIZE_Y, SIZE_Z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f)},
	{D3DXVECTOR3(SIZE_X, SIZE_Y, -SIZE_Z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f)},
	{D3DXVECTOR3(-SIZE_X, SIZE_Y, -SIZE_Z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f)},*/
	{D3DXVECTOR3(-SIZE_X, SIZE_Y,  SIZE_Z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(DICE_WIDHT, DICE_HEIGHT)},
	{D3DXVECTOR3(SIZE_X, SIZE_Y,  SIZE_Z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(DICE_WIDHT, H2)},
	{D3DXVECTOR3(-SIZE_X, SIZE_Y, -SIZE_Z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(W2, DICE_HEIGHT)},
	{D3DXVECTOR3(SIZE_X, SIZE_Y, SIZE_Z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(DICE_WIDHT, H2)},
	{D3DXVECTOR3(SIZE_X, SIZE_Y, -SIZE_Z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(W2, H2)},
	{D3DXVECTOR3(-SIZE_X, SIZE_Y, -SIZE_Z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(W2, DICE_HEIGHT)},
	
	//���@
	{D3DXVECTOR3(SIZE_X, -SIZE_Y,  SIZE_Z), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(W3, H2)},
	{D3DXVECTOR3(-SIZE_X, -SIZE_Y,  SIZE_Z), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(W3, DICE_HEIGHT)},
	{D3DXVECTOR3(-SIZE_X, -SIZE_Y, -SIZE_Z), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(W4, DICE_HEIGHT)},
	{D3DXVECTOR3(SIZE_X, -SIZE_Y, -SIZE_Z), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(W4, H2)},
	{D3DXVECTOR3(SIZE_X, -SIZE_Y, SIZE_Z), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(W3, H2)},
	{D3DXVECTOR3(-SIZE_X, -SIZE_Y, -SIZE_Z), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(W4, DICE_HEIGHT)},

	//���i���j
	{D3DXVECTOR3(-SIZE_X, -SIZE_Y,  -SIZE_Z), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, DICE_HEIGHT)},
	{D3DXVECTOR3(-SIZE_X, -SIZE_Y, SIZE_Z), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(DICE_WIDHT, DICE_HEIGHT)},
	{D3DXVECTOR3(-SIZE_X, SIZE_Y,  -SIZE_Z), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, H2)},
	{D3DXVECTOR3(-SIZE_X, SIZE_Y, SIZE_Z), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(DICE_WIDHT, H2)},
	{D3DXVECTOR3(-SIZE_X, SIZE_Y, -SIZE_Z), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, H2)},
	{D3DXVECTOR3(-SIZE_X, -SIZE_Y, SIZE_Z), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(DICE_WIDHT, DICE_HEIGHT)},

	//���i�E�j
	{D3DXVECTOR3(SIZE_X, -SIZE_Y, SIZE_Z), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(W3, DICE_HEIGHT)},
	{D3DXVECTOR3(SIZE_X, -SIZE_Y,  -SIZE_Z), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(W2, DICE_HEIGHT)},
	{D3DXVECTOR3(SIZE_X, SIZE_Y,  -SIZE_Z), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(W2, H2)},
	{D3DXVECTOR3(SIZE_X, SIZE_Y, -SIZE_Z), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(W2, H2)},
	{D3DXVECTOR3(SIZE_X, SIZE_Y, SIZE_Z), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(W3, H2)},
	{D3DXVECTOR3(SIZE_X, -SIZE_Y, SIZE_Z), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(W3, DICE_HEIGHT)},

	//����
	{D3DXVECTOR3(-SIZE_X, SIZE_Y,  -SIZE_Z), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(DICE_WIDHT, H2)},
	{D3DXVECTOR3(SIZE_X, SIZE_Y, -SIZE_Z), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(W2, H2)},
	{D3DXVECTOR3(-SIZE_X, -SIZE_Y,  -SIZE_Z), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(DICE_WIDHT, H3)},
	{D3DXVECTOR3(SIZE_X, SIZE_Y, -SIZE_Z), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(W2, H2)},
	{D3DXVECTOR3(SIZE_X, -SIZE_Y, -SIZE_Z), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(W2, H3)},
	{D3DXVECTOR3(-SIZE_X, -SIZE_Y, -SIZE_Z), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(DICE_WIDHT, H3)},

	//���
	{D3DXVECTOR3(SIZE_X, SIZE_Y, SIZE_Z), D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(W2, 0.0f)},
	{D3DXVECTOR3(-SIZE_X, SIZE_Y,  SIZE_Z), D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(DICE_WIDHT, 0.0f)},
	{D3DXVECTOR3(-SIZE_X, -SIZE_Y,  SIZE_Z), D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(DICE_WIDHT, DICE_HEIGHT)},
	{D3DXVECTOR3(SIZE_X, -SIZE_Y, SIZE_Z), D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(W2, DICE_HEIGHT)},
	{D3DXVECTOR3(SIZE_X, SIZE_Y, SIZE_Z), D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(W2, 0.0f)},
	{D3DXVECTOR3(-SIZE_X, -SIZE_Y, SIZE_Z), D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(DICE_WIDHT, DICE_HEIGHT)},
};


//=============================================================================
// ����������
//=============================================================================
HRESULT InitPolygon(void)
{
	// ���_�o�b�t�@�̍쐬
	MakeVertexPolygon();

	// �e�N�X�`������
	//g_TexNo = LoadTexture("data/TEXTURE/field000.jpg");
	g_TexNo = LoadTexture((char*)("data/TEXTURE/Dice (2).png"));

	// �ʒu�E��]�E�X�P�[���̏����ݒ�
	g_Polygon.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Polygon.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Polygon.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPolygon(void)
{
	// ���_�o�b�t�@�̉��
	if (g_VertexBuffer) {
		g_VertexBuffer->Release();
		g_VertexBuffer = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePolygon(void)
{
	CAMERA *cam = GetCamera();

	// ��]�������Ⴄ
	if (GetKeyboardPress(DIK_LEFT))
	{
		g_Polygon.rot.y -= VALUE_ROTATE;
	}
	if (GetKeyboardPress(DIK_RIGHT))
	{
		g_Polygon.rot.y += VALUE_ROTATE;
	}
	if (GetKeyboardPress(DIK_UP))
	{
		g_Polygon.rot.x -= VALUE_ROTATE;
	}
	if (GetKeyboardPress(DIK_DOWN))
	{
		g_Polygon.rot.x += VALUE_ROTATE;
	}

	if (GetKeyboardPress(DIK_SPACE))
	{
		g_Polygon.rot.y = g_Polygon.rot.x = 0.0f;
	}

#ifdef _DEBUG	// �f�o�b�O����\������
	char* str = GetDebugStr();
	sprintf(&str[strlen(str)], " rotX:%.2f rotY:%.2f", g_Polygon.rot.x, g_Polygon.rot.y);

#endif

	
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPolygon(void)
{
	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// �}�e���A���ݒ�
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	SetMaterial(material);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_TexNo));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Polygon.mtxWorld);

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl, g_Polygon.scl.x, g_Polygon.scl.y, g_Polygon.scl.z);
	D3DXMatrixMultiply(&g_Polygon.mtxWorld, &g_Polygon.mtxWorld, &mtxScl);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Polygon.rot.y, g_Polygon.rot.x, g_Polygon.rot.z);
	D3DXMatrixMultiply(&g_Polygon.mtxWorld, &g_Polygon.mtxWorld, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, g_Polygon.pos.x, g_Polygon.pos.y, g_Polygon.pos.z);
	D3DXMatrixMultiply(&g_Polygon.mtxWorld, &g_Polygon.mtxWorld, &mtxTranslate);



	// ���[���h�}�g���b�N�X�̐ݒ�
	SetWorldMatrix(&g_Polygon.mtxWorld);

	// �|���S���`��
	GetDeviceContext()->Draw(VERTEX_NUM, 0);
}

HRESULT MakeVertexPolygon(void)
{
	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;;
	bd.ByteWidth = sizeof(VERTEX_3D) * VERTEX_NUM;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	// �O���[�o���̒��_�z�񂩂璸�_�o�b�t�@������
	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = g_VertexArray;

	GetDevice()->CreateBuffer(&bd, &sd, &g_VertexBuffer);

	return S_OK;
}