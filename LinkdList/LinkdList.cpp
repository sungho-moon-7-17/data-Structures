#include "LinkdList.h"

LinkdList::LinkdList(){
    firstNode = nullptr;
    endNode = firstNode;
    countNode = 0;
}

LinkdList::~LinkdList(){
    LinkdList::Node * nextLinkdList;
    LinkdList::Node * curNode = firstNode;

    for(int i = 1; i <= countNode; i++){
        nextLinkdList = curNode->nextNode;
        delete(curNode);
        curNode = nextLinkdList;
    }
}

bool LinkdList::initLinkdList(){
    try{
        LinkdList::Node * nextLinkdList;
        LinkdList::Node * curNode = firstNode;

        for(int i = 1; i <= countNode; i++){
            nextLinkdList = curNode->nextNode;
            delete(curNode);
            curNode = nextLinkdList;
        }
        countNode = 0;
        return true;
    }
    catch (exception ex){
        return false;
    }
}

// addLinkdListNode 함수에서 첫 노드와 마지막 노드일 때 처리하는 함수
void LinkdList::addNodeFirstOrEnd(int addIndex, int addContent, LinkdList::Node * addNode){

	//현재 노드가 없으면
	if (!countNode){
		firstNode = addNode;					// firstNode를 업데이트 해준다.
		endNode = addNode;						// endNode에 addNode를 넣어준다.
	}
	// 마지막에 노드를 추가
	else if (addIndex > countNode){            
		addNode->prevNode = endNode->nextNode - sizeof(LinkdList::Node *);
		endNode->nextNode = addNode;            // 현재 마지막 노드의 nextNode에 추가한 노드를 넣어준다.
		endNode = addNode;
	}
	// 맨 앞에 노드를 추가
	else {
		firstNode->prevNode = addNode;
		addNode->nextNode = firstNode;
		firstNode = addNode;
	}
	
}

bool LinkdList::addLinkdListNode(unsigned int addIndex, int addContent){
    try{
        LinkdList::Node * addNode = new LinkdList::Node;
		LinkdList::Node * tempNode = firstNode;

		addNode->content = addContent;

		for(int i = FOR_FIRST_NUMBER; i <= countNode && i <= addIndex; i++)
			tempNode = tempNode->nextNode;		

		if(addIndex > countNode || addIndex == 1)
			addNodeFirstOrEnd(addIndex, addContent, addNode);
		else{
			addNode->prevNode = tempNode->prevNode;
			tempNode->prevNode->nextNode = addNode;
			addNode->nextNode = tempNode;
			tempNode->prevNode = addNode;
		}

        countNode++;

        return true;
    }
    catch(exception ex){
        return false;
    }
}

bool LinkdList::deletLinkdList_index(unsigned int delIndex)
{
	if(!countNode){
		cout << "Node가 없습니다." << endl;
		return false;
	}
    try{
        LinkdList::Node * delNode = firstNode;

        for(int i = FOR_FIRST_NUMBER ; i <= delIndex && i <= countNode; i++)
            delNode = delNode->nextNode;

        if(!delNode->nextNode)									
            endNode = delNode->prevNode;						// 마지막 노드면 마지막 노드를 가리키는 변수를  업데이트 한다.
		else if(firstNode == delNode)
			firstNode = delNode->nextNode;						// 첫 노드면 첫 노드를 가리키는 변수를 업데이트 한다.
		else{
			delNode->prevNode->nextNode = delNode->nextNode;	// 앞 순번의 노드의 다음노드를 가리키는 멤버를 지우는 노드의 다음 노드로 업데이트한다.
			delNode->nextNode->prevNode = delNode->prevNode;	// 위의 연산의 반대
		} 

        delete(delNode);

        countNode--;

        return true;
    }
    catch(exception ex){
        return false;
    }
}

bool LinkdList::deletLinkdList_content(int delContent)
{
    try{
        if (!firstNode)
            return false;

        int i;
        LinkdList::Node * delNode = firstNode;
		LinkdList::Node * prevDelNode = firstNode;

        for (i = 1; i <= countNode; i++){
            if (delNode->content == delContent)
                break;
            prevDelNode = delNode;
            delNode = delNode->nextNode;
        }

		if (i > countNode){
			return false;
		}
        else if(!delNode->nextNode)									
            endNode = delNode->prevNode;						// 마지막 노드면 마지막 노드를 가리키는 변수를  업데이트 한다.
		else if(firstNode == delNode)
			firstNode = delNode->nextNode;						// 첫 노드면 첫 노드를 가리키는 변수를 업데이트 한다.
		else{
			delNode->prevNode->nextNode = delNode->nextNode;	// 앞 순번의 노드의 다음노드를 가리키는 멤버를 지우는 노드의 다음 노드로 업데이트한다.
			delNode->nextNode->prevNode = delNode->prevNode;	// 위의 연산의 반대
		} 
        
        prevDelNode->nextNode = delNode->nextNode;      // 서로의 노드를 이어준다.
        delete(delNode);
        countNode--;
        return true;
    }
    catch (exception ex){
        return false;
    }
}

int LinkdList::searchLinkdList_index(unsigned int searchIndex)
{
    LinkdList::Node * tempNode = firstNode;
    int i;

    for(i = FOR_FIRST_NUMBER; i <= searchIndex && i <= countNode; i++) // firstNode를 넣어서 2부터 시작한다.
        tempNode = tempNode->nextNode;
    
    // i의 값이 반복문에서 증가해서 -1을 해줌
    std::cout << i - 1 << "번째 리스트의 값은 == " << tempNode->content << std::endl;

    return tempNode->content;
}

int LinkdList::searchLinkdList_content(int searchContent){
    LinkdList::Node *tempNode = firstNode;

    for(int i = FOR_FIRST_NUMBER; i <= countNode; i++)
    {
        if (tempNode->content == searchContent){
            std::cout << "찾으시는 " << searchContent << "값은 " << i << "번째에 있습니다." << std::endl;
            return i;
        }
    }

    std::cout << "찾으시는 " << searchContent << "은(는) 없습니다." << std::endl;
    return -1;
}

void LinkdList::showAllData(){
    LinkdList::Node *tempNode = firstNode;

    cout << "\n\n=============================" << endl;

    if(!countNode){
        std::cout << "데이터가 없습니다." << std::endl;
        cout << "=============================\n" << endl;
        return ;
    }

    for(int i = 1; i <= countNode; i++)
    {
        std::cout << i << "번 데이터는 == " << tempNode->content << std::endl;
        tempNode = tempNode->nextNode;
    }
    cout << "=============================\n\n" << endl;
}

int LinkdList::replaceNodeContent(unsigned int replaceIndex, int replaceContent){
	LinkdList::Node * tempNode = firstNode;
    int curNodeOldValue = 0;

	for(int i = FOR_FIRST_NUMBER; i <= replaceIndex && i <= countNode; i++)
		tempNode = tempNode->nextNode;
		
    curNodeOldValue = tempNode->content;
    tempNode->content = replaceContent;

    return curNodeOldValue;
}