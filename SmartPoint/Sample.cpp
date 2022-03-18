#include <iostream>
#include <vector>
#include <memory>
struct JNode
{
	int iValue;
	JNode(int i)
	{
		iValue = i;
	}
	JNode()
	{
		iValue = 0;
	}
};
using J_Node = std::shared_ptr<JNode>;
class Manager1
{
	std::vector<std::unique_ptr<JNode>> list;
public:
	void Add(int data)
	{
		list.push_back(std::make_unique<JNode>(data));
	};
	JNode& GetPtr(int iData)
	{
		for (auto& data : list)
		{
			if (data->iValue == iData)
			{
				return *data;
			}
		}
	}
	JNode* GetPtr3(int iData)
	{
		for (auto& data : list)
		{
			if (data->iValue == iData)
			{
				return data.get();
			}
		}
		return nullptr;
	}
	std::unique_ptr<JNode>& GetPtr2(int iData)
	{
		//for (auto data : list)
		std::vector<std::unique_ptr<JNode>>::iterator iter;
		for (iter = list.begin();
			iter != list.end();
			iter++)
		{
			if ((*iter)->iValue == iData)
			{
				return *iter;
			}
		}
	}
};
class Manager2
{
	std::vector<std::shared_ptr<JNode>> list;
public:
	void Add(int data)
	{
		list.push_back(std::make_shared<JNode>(data));
	};
	JNode& GetPtr(int iData)
	{
		for (auto& data : list)
		{
			if (data->iValue == iData)
			{
				return *data;
			}
		}
	}
	std::shared_ptr<JNode> GetPtr2(int iData)
	{
		for (auto data : list)
		{
			if (data->iValue == iData)
			{
				return data;
			}
		}
	}
};
void main()
{
	/*std::vector<T_Node>  list;
	list.push_back(T_Node(new TNode));
	TNode* pNode = list[0].get();
	auto data = list[0];
	std::cout << data.get()->iValue<<std::endl;
	std::cout << data->iValue << std::endl;*/

	//std::vector<std::shared_ptr<int>> data3;
	//data3.push_back(std::make_shared<int>(4));
	//std::vector<std::shared_ptr<int>> data4;
	//std::shared_ptr<int> aa = data3[0];
	////*data4[0].get() = 9;

	std::vector<std::unique_ptr<int>> data1;
	data1.push_back(std::make_unique<int>(4));
	std::vector<std::unique_ptr<int>> data2;
	//data2 = data1;
	//std::unique_ptr<int> copy = data1
	data2 = std::move(data1);
	//*data2[0].get() = 9;

	/*std::vector<std::unique_ptr<int>> data1(10);
	std::vector<std::unique_ptr<int>> data2;
	data2 = data1;*/



	Manager1 mgr1;
	for (int i = 0; i < 3; i++)
	{
		mgr1.Add(i);
	}



	JNode& node1 = mgr1.GetPtr(2);
	node1.iValue = 10;

	std::unique_ptr<JNode>& copy = mgr1.GetPtr2(1);
	copy.get()->iValue = 10;

	Manager2 mgr2;
	for (int i = 0; i < 3; i++)
	{
		mgr2.Add(i);
	}
	JNode& node2 = mgr2.GetPtr(2);
	node2.iValue = 10;

	//  weak_ptr  �����Ϳ� ���� ���� �Ұ�(�������,�Լ� ��� ��� �Ұ�)
	//  ������ ������� lock()�� ����Ѵ�.
		//  shared_ptr�� ��ȯ �޴´�.
	std::shared_ptr<int > w1(new int(3));
	std::weak_ptr<int> weak1 = w1;
	*w1.get() = 5;
	//*weak1.get() = 44;
	std::shared_ptr<int > obj = weak1.lock();
	*obj.get() = 44;

}
