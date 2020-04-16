#include"Cable.h"

//�������𑍊�
bool Cable::Initialize()
{
	ModelInitialize();
	StatusInitialize();
	ObbInitialize();

	return true;
}
//�P�[�u�����f���̏�����
bool Cable::ModelInitialize() 
{
	//3D���f���̃^�C�v�A�`��̐ݒ�
	SimpleShape shape;

	shape.Type    = Shape_Cylinder;
	shape.Radius1 = 0.5f;
	shape.Radius2 = 0.5f;
	shape.Length  = 1.0f;
	shape.Slices  = 50.0f;
	shape.Stacks  = 20.0f;

	//�}�e���A��RGB�J���[�̏�����
	R_ = 1.0f; 
	G_ = 1.0f; 
	B_ = 1.0f;

	//�}�e���A���̏�����
	mtrl.Diffuse = Color(R_, G_, B_);
	mtrl.Ambient = Color(R_, G_, B_);

	for (int i = 0; i < 3; i++)
	{
		//�v���C���[�̈ʒu�ɂ���ĉ������ɐL�т�P�[�u��
		cable_[i] = GraphicsDevice.CreateModelFromSimpleShape(shape); //���f���̏�����
		cable_[i]->SetPosition(0, 2.0, 0);                            //���W�̏�����
		cable_[i]->SetMaterial(mtrl);                                 //�}�e���A���̓K��

		//���������ۉ��ɐL�т�P�[�u��
		//fall_cable_[i] = GraphicsDevice.CreateModelFromSimpleShape(shape); 
		//fall_cable_[i]->SetMaterial(mtrl);
	}

	return true;
}
//OBB�֘A�̏�����
bool Cable::ObbInitialize()
{
	//�P�[�u����OBB���擾
	for (int i = 0; i < 3; i++)
	{
		cable_obb_ = cable_[i]->GetOBB();
		cable_obb_.Center = cable_[i]->GetPosition();
	}
	cable_obb_.Radius = Vector3(100.0f, 1, 100.0f);

	//OBB�\���p�̃��f��
	SimpleShape shape_;
	shape_.Type = Shape_Box;
	{
		shape_.Width = 1;
		shape_.Height = 1;
		shape_.Depth = 1;
	}
	obb_mad_ = GraphicsDevice.CreateModelFromSimpleShape(shape_);
	obb_mad_->SetMaterial(mtrl);

	return true;
}
//�X�e�[�^�X�̏�����
bool Cable::StatusInitialize()
{
	for (int i = 0; i < 3; i++)
	{
		dist[i] = 0.0f;
	}
	return true;
}

void Cable::Update()
{

	//------------------------------------------------------------------------
	//���ɒu���Ă邾��(��ňړ�������)//

	//Y���𔲂���2�_�Ԃ̋���(Vector3_Distance��Y������Ver)
	auto Cable_Distance = [&](Vector3& a, Vector3& b)
	{
		float  x = (a.x - b.x) * (a.x - b.x) + (a.z - b.z) * (a.z - b.z);
		float  y = sqrt(x);
		return y;
	};
	//Y���݂̂�2�_�Ԃ̋���
	auto Fall_Distance = [&](Vector3& a, Vector3& b)
	{
		float  x = a.y - b.y;
		return x;
	};
	//------------------------------------------------------------------------
}

void Cable::Draw3D()
{

	ObbDraw();
}
void Cable::ObbDraw()
{

	for (int i = 0; i < 3; i++)
	{
		//�P�[�u����OBB������(�f�o�b�O�p)

		/*�P�[�u����OBB��\������  �c  true
					   �\�����Ȃ�  �c  false
		*/
		bool debug_obb_drow = false;

		if (debug_obb_drow)
		{
			OrientedBoundingBox obb = cable_[i]->GetOBB();

			Matrix dir = Matrix_Identity();
			CopyMemory(&dir._11, obb.Axis[0], sizeof(float) * 3);
			CopyMemory(&dir._21, obb.Axis[1], sizeof(float) * 3);
			CopyMemory(&dir._31, obb.Axis[2], sizeof(float) * 3);

			obb_mad_->SetPosition(obb.Center);
			obb_mad_->SetScale(obb.Radius.x * 2, obb.Radius.y * 2, obb.Radius.z * 2);
			obb_mad_->SetDirection(Quaternion_CreateFromRotationMatrix(dir));
			obb_mad_->Draw();
		}
	}
}