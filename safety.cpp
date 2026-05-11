#include <iostream>
#include <iomanip>
#include<string>
#include<limits.h>
#include<utility>
#include<vector>
#include<queue>
#include<algorithm>
#include <unordered_set>
#include <sstream>
#include <string>
#include <unordered_set>
#include <functional>


using namespace std;

template <class T>
class VecList {
private:
    int capacity;
    int length;
    T* arr;
    void doubleListSize() {
        T* oldArr = arr;
        arr = new T[2 * capacity];
        capacity = 2 * capacity;
        for (int i = 0; i < length; i++) {
            arr[i] = oldArr[i];
        }
        delete[] oldArr;
    }
public:
    VecList() {
        length = 0;
        capacity = 100;
        arr = new T[capacity];
    }
    VecList(T* a, int n) {
        length = n;
        capacity = 100 + 2 * n;
        arr = new T[capacity];
        for (int i = 0; i < n; i++) {
            arr[i] = a[i];
        }
    }
    VecList(const VecList<T>& other) : capacity(other.capacity), length(other.length), arr(new T[other.capacity]) {
        for (int i = 0; i < other.length; i++) {
            arr[i] = other.arr[i];
        }
    }
    VecList<T>& operator=(const VecList<T>& other) {
        if (this != &other) {
            // 释放当前资源
            delete[] arr;

            // 复制基本数据
            capacity = other.capacity;
            length = other.length;

            // 分配新内存并复制元素
            arr = new T[capacity];
            for (int i = 0; i < length; i++) {
                arr[i] = other.arr[i];
            }
        }
        return *this;
    }
    bool operator==(const VecList<T>&other) {
        if (length != other.length) return false;
        for (int i = 0; i < length; i++)
        {
            if (arr[i] != other.arr[i]) return false;
        }
        return true ;
    }
    ~VecList() {
        delete[] arr;
    }
    bool contains(const T& element) const {
        for (int i = 0; i < length; i++) {
            if (arr[i] == element)
                return true;
        }
        return false;
    }

    int getLength() {
        return length;
    }
    bool isEmpty() {
        return length == 0;
    }
    void clear() 
    { length = 0; }
    void insertEleAtPos(int i, T x) {
        if (length == capacity)
            doubleListSize();
        if (i > length || i < 0)
            throw "Illegal position";
        for (int j = length; j > i; j--)
            arr[j] = arr[j - 1];
        arr[i] = x;
        length++;
    }
    T deleteEleAtPos(int i) {
        if (i >= length || i < 0) 
            throw "Illegal position";
        T tmp = arr[i];
        for (int j = i; j < length - 1; j++)
            arr[j] = arr[j + 1];
        length--;
        return tmp;
    }
    void setEleAtPos(int i, T x) {
        if (i >= length || i < 0)
            throw "Illegal position";
        arr[i] = x;
    }
    T getEleAtPos(int i) {
        if (i >= length || i < 0)
            throw "Illegal position";
        return arr[i];
    }
    int locateEle(T x) {
        for (int i = 0; i < length; i++) {
            if (arr[i] == x)
                return i;
        }
        return -1;
    }
    void insertLast(T x) {
        insertEleAtPos(length, x);
    }
    void printList() {
        for (int i = 0; i < length; i++)
            cout << arr[i] << " ";
    }
};

template <class T>
struct DNode {
    T data;
    DNode<T>* next;
};

template <class T>
class LinkStack {
private:
    DNode<T>* top;
    int length;
public:
    LinkStack() {
        top = NULL;
        length = 0;
    }
    ~LinkStack() {
        while (top != NULL) {
            DNode<T>* tmp = top;
            top = top->next;
            delete tmp;
        }
    }
    int getLength() {
        return length;
    }
    bool isEmpty() {
        return length == 0;
    }
    void clear() { length = 0; }
    void push(T x) {
        DNode<T>* tmp = new DNode<T>;
        tmp->data = x;
        tmp->next = top;
        top = tmp;
        length++;
    }
    T pop() {
        if (length == 0) throw "Stack Empty!";
        DNode<T>* tmp = top;
        top = top->next;
        T tmpData = tmp->data;
        delete tmp;
        length--;
        return tmpData;
    }
    T getTop() {
        if (length == 0) throw "Stack Empty!";
        return top->data;
    }
    void printStack() {
        cout << "Stack top: ";
        DNode<T>* tmp = top;
        while (tmp != NULL) {
            cout << tmp->data << " ";
            tmp = tmp->next;
        }
        cout << ":stack bottom" << endl;
    }
};

template <class T>
class LinkQueue {
private:
    DNode<T>* front;
    DNode<T>* back;
    int length;
public:
    LinkQueue() {
        front = new DNode<T>;
        front->next = NULL;
        back = front;
        length = 0;
    }
    ~LinkQueue() {
        while (front != NULL) {
            back = front;
            front = front->next;
            delete back;
        }
    }
    int getLength() {
        return length;
    }
    bool isEmpty() {
        return length == 0;
    }
    void enQueue(T x) {
        DNode<T>* tmpN = new DNode<T>;
        tmpN->data = x;
        tmpN->next = NULL;
        back->next = tmpN;
        back = tmpN;
        length++;
    }
    T deQueue() {
        if (length == 0) throw "Queue Empty!";
        DNode<T>* tmpN = front->next;
        front->next = tmpN->next;
        T tmpD = tmpN->data;
        delete tmpN;
        length--;
        if (length == 0) back = front;
        return tmpD;
    }
    T peekQueue() {
        if (length == 0) throw "Queue Empty!";
        return front->next->data;
    }
    void printQueue() {
        cout << "Front of queue: ";
        DNode<T>* tmp = front->next;
        while (tmp != NULL) {
            cout << tmp->data << " ";
            tmp = tmp->next;
        }
        cout << ": back of queue" << endl;
    }
};

template <class T>
struct Edge {
    T start;
    T end;
    int weight;
};





template <class T>
class AMGraph { 
    //we need the number of vertices fixed if we are using this approach
    //our edges don't contain weights here.
public:
    int numVer, numEdge;
    VecList<T> verList; // list of vertices
    int** adjMatrix;
    int** originaladjMatrix;
    bool directed;
    vector<vector<int>> adjList;
    

    AMGraph() { // we don't want this used.
    }

    AMGraph(VecList<T>nodes, int n, bool dir = false) {
        // n for number of vertices
        // default for undirected graph
        // edges to be added later.

        numVer = n;
        numEdge = 0;
        for (int i = 0; i < n; i++) {
            verList.insertLast(nodes.getEleAtPos(i));
        }
        directed = dir;
        adjMatrix = new int* [n];
        originaladjMatrix = new int* [n];
        for (int i = 0; i < n; i++) {
            adjMatrix[i] = new int[n];
            originaladjMatrix[i] = new int[n];
            for (int j = 0; j < n; j++)
            {
                adjMatrix[i][j] = 0;
                originaladjMatrix[i][j] = 0;
            }
            
        }
    }
    
    AMGraph(T* arr, int n, Edge<T>** eArr, int e, bool dir = false) {
        // n for number of vertices
        // default for undirected graph
        // edges to be added now.

        numVer = n;
        numEdge = 0;
        for (int i = 0; i < n; i++) {
            verList.insertLast(arr[i]);
        }
        directed = dir;
        for (int i = 0; i < n; i++) 
        {
            cout << verList.getEleAtPos(i) << endl;
        }
        adjMatrix = new int* [n];
        for (int i = 0; i < n; i++) {
            adjMatrix[i] = new int[n];
            for (int j = 0; j < n; j++)
                adjMatrix[i][j] = 0;
        }

        for (int i = 0; i < e; i++) {
            addEdge(eArr[i]->start, eArr[i]->end, eArr[i]->weight);
        }
    }
    
    ~AMGraph() {
        for (int i = 0; i < numVer; i++) {
            delete[] adjMatrix[i];
        }
        delete[] adjMatrix;
    }
    
    
    void addEdge(Edge<T> e) {
        addEdge(e.start, e.end, e.weight);
    }
    
    void addEdge(T st, T en, int weight) {
        int sIndex = verList.locateEle(st);
        int eIndex = verList.locateEle(en);
        if (sIndex == -1 || eIndex == -1)cout << "Wrong Input!" << endl;
        if (adjMatrix[sIndex][eIndex] == 0)
        {
            numEdge++;
        }
        if (originaladjMatrix[sIndex][eIndex] == 0)
        {
            originaladjMatrix[sIndex][eIndex] = weight;
            originaladjMatrix[eIndex][sIndex] = weight;
        }
        adjMatrix[sIndex][eIndex] = weight;
        if (!directed) adjMatrix[eIndex][sIndex] = weight;
    }
    
    void removeEdge(Edge<T> e) {
        removeEdge(e.start, e.end);
    }
    
    int getOriginalWeight(T st, T en) {
        int sIndex = verList.locateEle(st);
        int eIndex = verList.locateEle(en);
        return  originaladjMatrix[sIndex][eIndex];
    }
    
    void removeEdge(T st, T en) {
        int sIndex = verList.locateEle(st);
        int eIndex = verList.locateEle(en);
        if (adjMatrix[sIndex][eIndex] == 0) return;
        numEdge--;
        adjMatrix[sIndex][eIndex] = 0;
        if (!directed) adjMatrix[eIndex][sIndex] = 0;
    }
    
    int** getMatrix() const {
        return adjMatrix;
    }

    int getweight(T a, T b) const {
        int index1 = verList.locateEle(a);
        int index2 = verList.locateEle(b);
        if (index1 == -1 || index2 == -1) return INT_MAX;
        if (adjMatrix[index1][index2] == 0) return INT_MAX;
        return adjMatrix[index1][index2];
    }

    int getposInver(T x) const {
        return verList.locateEle(x);
    }

    
    pair<VecList<T>, int> DijkstraTotwopoint(T source, T destination, bool* bannedNodes, 
                                      int maxIntermediateCount, VecList<T> prefixPath)
{
    // 1. 初始化数据结构
    bool* visited = new bool[numVer];        // 是否已找到最短路径
    int* distance = new int[numVer];         // 起点到各点的最短距离
    int* predecessor = new int[numVer];      // 前驱节点索引
    int* intermediateCount = new int[numVer]; // 中继点计数
    
    // 计算中继点限制
    int intermediateLimit = -1;
    if (maxIntermediateCount != -1) {
        intermediateLimit = maxIntermediateCount - prefixPath.getLength() + 2;
    }
    
    // 初始化所有数组
    for (int i = 0; i < numVer; i++) {
        visited[i] = false;
        distance[i] = INT_MAX;
        predecessor[i] = -1;
        intermediateCount[i] = 0;
    }
    
    // 2. 获取起点和终点的索引
    int startIdx = verList.locateEle(source);
    int endIdx = verList.locateEle(destination);
    
    // 检查起点和终点的有效性
    if (startIdx == -1 || endIdx == -1 || bannedNodes[startIdx] || bannedNodes[endIdx]) {
        // 清理内存并返回无效路径
        delete[] visited;
        delete[] distance;
        delete[] predecessor;
        delete[] intermediateCount;
        return make_pair(VecList<T>(), INT_MAX);
    }
    
    // 3. 处理前缀路径（在Yen's算法中使用）
    visited[startIdx] = true;
    distance[startIdx] = 0;
    
    for (int i = 0; i < prefixPath.getLength(); i++) {
        int nodeIdx = verList.locateEle(prefixPath.getEleAtPos(i));
        visited[nodeIdx] = true;
    }
    
    // 4. 初始化起点相邻节点
    for (int i = 0; i < numVer; i++) {
        if (bannedNodes[i] || adjMatrix[startIdx][i] == 0) {
            continue;
        }
        distance[i] = adjMatrix[startIdx][i];
        predecessor[i] = startIdx;
        intermediateCount[i] = 1;  // 起点到相邻节点有1个中继点
    }
    
    // 5. Dijkstra主循环
    int visitedCount = 1;
    while (visitedCount < numVer) {
        int currentIdx = -1;
        int minDistance = INT_MAX;
        
        // 选择未访问节点中距离最小的
        for (int i = 0; i < numVer; i++) {
            if (visited[i] || distance[i] == INT_MAX || bannedNodes[i]) {
                continue;
            }
            if (intermediateLimit != -1 && intermediateCount[i] > intermediateLimit) {
                continue;
            }
            if (distance[i] < minDistance) {
                currentIdx = i;
                minDistance = distance[i];
            }
        }
        
        // 如果没有合适的节点，结束循环
        if (currentIdx == -1) {
            break;
        }
        
        // 标记当前节点为已访问
        visited[currentIdx] = true;
        visitedCount++;
        
        // 更新当前节点的邻居
        for (int neighbor = 0; neighbor < numVer; neighbor++) {
            // 跳过条件：在黑名单中、已访问、没有边连接
            if (bannedNodes[neighbor] || visited[neighbor] || 
                adjMatrix[currentIdx][neighbor] == 0) {
                continue;
            }
            
            int newDist = distance[currentIdx] + adjMatrix[currentIdx][neighbor];
            int newIntermediates = intermediateCount[currentIdx] + 1;
            
            // 检查是否满足中继点限制
            bool meetsLimit = (intermediateLimit == -1) || (newIntermediates <= intermediateLimit);
            
            // 如果找到更短路径且满足限制，更新
            if (newDist < distance[neighbor] && meetsLimit) {
                distance[neighbor] = newDist;
                predecessor[neighbor] = currentIdx;
                intermediateCount[neighbor] = newIntermediates;
            }
        }
    }
    
    // 6. 构建最短路径
    VecList<T> path;
    int totalDistance = INT_MAX;
    
    if (distance[endIdx] != INT_MAX) {
        // 使用栈来反向构建路径
        LinkStack<int> pathStack;
        int currentNode = endIdx;
        
        // 从终点回溯到起点
        while (currentNode != -1) {
            pathStack.push(currentNode);
            currentNode = predecessor[currentNode];
        }
        
        // 将路径从栈中取出，得到正向路径
        while (!pathStack.isEmpty()) {
            int nodeIdx = pathStack.pop();
            path.insertLast(verList.getEleAtPos(nodeIdx));
        }
        
        totalDistance = distance[endIdx];
    }
    
    // 7. 清理动态分配的内存
    delete[] visited;
    delete[] distance;
    delete[] predecessor;
    delete[] intermediateCount;
    
    return make_pair(path, totalDistance);
}

    int getweight(T a, T b)
    {
        int index1 = verList.locateEle(a);
        int index2 = verList.locateEle(b);
        return adjMatrix[index1][index2];
    }
    
    int getposInver(T x)
    {
        return verList.locateEle(x);
    }

};



void printMartix(int m, int** arr)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << arr[i][j]<<" ";
        }
        cout << endl;
    }
}

template <class T>
class Solution {
public:
    AMGraph<T> G;
    bool* if_ban;
    int limit;
    VecList<VecList<T>> paths;
    VecList<int> totalweights;
    int nodesnum;
    VecList<T> nodes;
    int edgesnum;
    
    Solution() {
        if_ban = nullptr;
        limit = -1;
        nodesnum = 0;
        edgesnum = 0;
    }
    
    Solution(int m, int n, VecList<T> strings, vector<Edge<T>> edges): G(strings, m) {
        nodesnum = m;
        edgesnum = n;
        if_ban = new bool[nodesnum];
        limit = -1;
        
        for (int i = 0; i < nodesnum; i++) {
            if_ban[i] = false;
            nodes.insertLast(strings.getEleAtPos(i));
        }
        
        for (int i = 0; i < n; i++) {
            G.addEdge(edges[i]);
        }
    }
    
    ~Solution() {
        if (if_ban != nullptr) {
            delete[] if_ban;
        }
    }
    
    bool if_In(VecList<T> path) {
        for (int i = 0; i < paths.getLength(); i++) {
            if (paths.getEleAtPos(i) == path) {
                return true;
            }
        }
        return false;
    }
    
    int getpathweight(VecList<T> path) {
        int pathweight = 0;
        for (int i = 0; i < path.getLength() - 1; i++) {
            int w = G.getweight(path.getEleAtPos(i), path.getEleAtPos(i + 1));
            if (w == INT_MAX) {
                return INT_MAX;
            }
            pathweight += w;
        }
        return pathweight;
    }
    
    void addpath(VecList<T> path, int weight) {
        if (if_In(path) || path.isEmpty() || weight == INT_MAX) {
            return;
        }
        
        if (paths.isEmpty()) {
            paths.insertLast(path);
            totalweights.insertLast(weight);
            return;
        }
        
        int pos = 0;
        while (pos < totalweights.getLength() && totalweights.getEleAtPos(pos) < weight) {
            pos++;
        }
        paths.insertEleAtPos(pos, path);
        totalweights.insertEleAtPos(pos, weight);
    }
    
    // 新增：检查节点是否被禁止的函数
    bool isBanned(T node) {
        int pos = nodes.locateEle(node);
        if (pos == -1) {
            // 节点不存在，也视为"禁止"状态
            return true;
        }
        return if_ban[pos];
    }
    
    // 新增：输出结果的函数
    void printResults() {
        if (paths.getLength() == 0) {
            cout << "There are 0 paths." << endl;
            return;
        }
        
        if (paths.getLength() == 1) {
            cout << "There is " << paths.getLength() << " path:" << endl;
        } else {
            cout << "There are " << paths.getLength() << " paths:" << endl;
        }
        
        for (int i = 0; i < paths.getLength(); i++) {
            cout << "Path " << i << ": ";
            VecList<T> currentPath = paths.getEleAtPos(i);
            
            for (int j = 0; j < currentPath.getLength(); j++) {
                cout << currentPath.getEleAtPos(j);
                if (j < currentPath.getLength() - 1) {
                    cout << "->";
                }
            }
            cout << ", distance = " << totalweights.getEleAtPos(i) << endl;
        }
    }
    
    void minpaths(T start, T end, int K) {
        // 首先检查起点和终点是否被禁止
        if (isBanned(start) || isBanned(end)) {
            cout << "Illegal option! Node has been banned!" << endl;
            return;
        }
        
        paths.clear();
        totalweights.clear();
        
        // 找到第一条最短路径
        VecList<T> emptyPath;
        pair<VecList<T>, int> firstResult = G.DijkstraTotwopoint(start, end, if_ban, limit, emptyPath);
        
        if (firstResult.second == INT_MAX) {
            cout << "There are 0 paths." << endl;
            return;
        }
        
        VecList<T> firstPath = firstResult.first;
        int firstWeight = firstResult.second;
        addpath(firstPath, firstWeight);
        
        // 存储所有候选路径及其权重
        VecList<VecList<T>> candidatePaths;
        VecList<int> candidateWeights;
        
        // 对于已经找到的每条路径，生成候选路径
        for (int pathIndex = 0; pathIndex < paths.getLength(); pathIndex++) {
            VecList<T> currentPath = paths.getEleAtPos(pathIndex);
            int currentPathLength = currentPath.getLength();
            
            // 对当前路径的每个节点（除了终点）作为spur节点
            for (int spurIndex = 0; spurIndex < currentPathLength - 1; spurIndex++) {
                T spurNode = currentPath.getEleAtPos(spurIndex);
                
                // 构建根路径（从起点到spur节点）
                VecList<T> rootPath;
                for (int i = 0; i <= spurIndex; i++) {
                    rootPath.insertLast(currentPath.getEleAtPos(i));
                }
                
                // 临时移除会导致重复路径的边
                vector<pair<T, T>> removedEdges;
                vector<int> removedWeights;
                
                // 检查所有已找到的路径
                for (int foundPathIndex = 0; foundPathIndex < paths.getLength(); foundPathIndex++) {
                    VecList<T> foundPath = paths.getEleAtPos(foundPathIndex);
                    
                    // 检查是否有相同的前缀
                    bool samePrefix = true;
                    for (int i = 0; i <= spurIndex; i++) {
                        if (i >= foundPath.getLength() || foundPath.getEleAtPos(i) != rootPath.getEleAtPos(i)) {
                            samePrefix = false;
                            break;
                        }
                    }
                    
                    // 如果前缀相同且路径有下一个节点，则临时移除边
                    if (samePrefix && foundPath.getLength() > spurIndex + 1) {
                        T nextNode = foundPath.getEleAtPos(spurIndex + 1);
                        int originalWeight = G.getOriginalWeight(spurNode, nextNode);
                        
                        G.removeEdge(spurNode, nextNode);
                        removedEdges.push_back(make_pair(spurNode, nextNode));
                        removedWeights.push_back(originalWeight);
                    }
                }
                
                // 查找从spur节点到终点的最短路径
                pair<VecList<T>, int> spurResult = G.DijkstraTotwopoint(
                    spurNode, end, if_ban, limit, rootPath);
                
                if (spurResult.second != INT_MAX) {
                    VecList<T> spurPath = spurResult.first;
                    
                    // 合并根路径和分支路径
                    VecList<T> combinedPath = rootPath;
                    bool hasCycle = false;
                    
                    // 从第二个节点开始合并（第一个节点已在rootPath中）
                    for (int i = 1; i < spurPath.getLength(); i++) {
                        T currentNode = spurPath.getEleAtPos(i);
                        
                        if (combinedPath.contains(currentNode)) {
                            hasCycle = true;
                            break;
                        }
                        
                        combinedPath.insertLast(currentNode);
                    }
                    
                    // 如果路径有效且无环路，加入候选列表
                    if (!hasCycle && !combinedPath.isEmpty()) {
                        int combinedWeight = getpathweight(combinedPath);
                        
                        // 检查是否已存在于结果路径中
                        bool alreadyInResults = false;
                        for (int j = 0; j < paths.getLength(); j++) {
                            if (paths.getEleAtPos(j) == combinedPath) {
                                alreadyInResults = true;
                                break;
                            }
                        }
                        
                        // 检查是否已存在于候选列表中
                        bool alreadyInCandidates = false;
                        for (int j = 0; j < candidatePaths.getLength(); j++) {
                            if (candidatePaths.getEleAtPos(j) == combinedPath) {
                                alreadyInCandidates = true;
                                break;
                            }
                        }
                        
                        if (!alreadyInResults && !alreadyInCandidates) {
                            // 按权重顺序插入候选列表
                            int insertPos = 0;
                            while (insertPos < candidateWeights.getLength() && 
                                   candidateWeights.getEleAtPos(insertPos) < combinedWeight) {
                                insertPos++;
                            }
                            candidatePaths.insertEleAtPos(insertPos, combinedPath);
                            candidateWeights.insertEleAtPos(insertPos, combinedWeight);
                        }
                    }
                }
                
                // 恢复临时移除的边
                for (unsigned int e = 0; e < removedEdges.size(); e++) {
                    G.addEdge(removedEdges[e].first, removedEdges[e].second, removedWeights[e]);
                }
            }
        }
        
        // 继续寻找更多路径，直到找到K条或没有候选路径
        while (paths.getLength() < K && candidatePaths.getLength() > 0) {
            // 取出第一个候选路径（权重最小的）
            VecList<T> nextPath = candidatePaths.getEleAtPos(0);
            int nextWeight = candidateWeights.getEleAtPos(0);
            
            // 从候选列表中移除
            candidatePaths.deleteEleAtPos(0);
            candidateWeights.deleteEleAtPos(0);
            
            // 添加到结果中
            addpath(nextPath, nextWeight);
            
            // 基于这条新找到的路径生成更多候选路径
            int newPathIndex = paths.getLength() - 1; // 新添加的路径的索引
            VecList<T> newPath = paths.getEleAtPos(newPathIndex);
            int newPathLength = newPath.getLength();
            
            for (int spurIndex = 0; spurIndex < newPathLength - 1; spurIndex++) {
                T spurNode = newPath.getEleAtPos(spurIndex);
                
                // 构建根路径
                VecList<T> rootPath;
                for (int i = 0; i <= spurIndex; i++) {
                    rootPath.insertLast(newPath.getEleAtPos(i));
                }
                
                // 临时移除会导致重复路径的边
                vector<pair<T, T>> removedEdges;
                vector<int> removedWeights;
                
                // 检查所有已找到的路径（包括新找到的这条）
                for (int foundPathIndex = 0; foundPathIndex < paths.getLength(); foundPathIndex++) {
                    VecList<T> foundPath = paths.getEleAtPos(foundPathIndex);
                    
                    // 检查是否有相同的前缀
                    bool samePrefix = true;
                    for (int i = 0; i <= spurIndex; i++) {
                        if (i >= foundPath.getLength() || foundPath.getEleAtPos(i) != rootPath.getEleAtPos(i)) {
                            samePrefix = false;
                            break;
                        }
                    }
                    
                    if (samePrefix && foundPath.getLength() > spurIndex + 1) {
                        T nextNode = foundPath.getEleAtPos(spurIndex + 1);
                        int originalWeight = G.getOriginalWeight(spurNode, nextNode);
                        
                        G.removeEdge(spurNode, nextNode);
                        removedEdges.push_back(make_pair(spurNode, nextNode));
                        removedWeights.push_back(originalWeight);
                    }
                }
                
                // 查找从spur节点到终点的最短路径
                pair<VecList<T>, int> spurResult = G.DijkstraTotwopoint(
                    spurNode, end, if_ban, limit, rootPath);
                
                if (spurResult.second != INT_MAX) {
                    VecList<T> spurPath = spurResult.first;
                    
                    // 合并根路径和分支路径
                    VecList<T> combinedPath = rootPath;
                    bool hasCycle = false;
                    
                    for (int i = 1; i < spurPath.getLength(); i++) {
                        T currentNode = spurPath.getEleAtPos(i);
                        
                        if (combinedPath.contains(currentNode)) {
                            hasCycle = true;
                            break;
                        }
                        
                        combinedPath.insertLast(currentNode);
                    }
                    
                    if (!hasCycle && !combinedPath.isEmpty()) {
                        int combinedWeight = getpathweight(combinedPath);
                        
                        // 检查是否已存在
                        bool alreadyExists = false;
                        for (int j = 0; j < paths.getLength(); j++) {
                            if (paths.getEleAtPos(j) == combinedPath) {
                                alreadyExists = true;
                                break;
                            }
                        }
                        for (int j = 0; j < candidatePaths.getLength(); j++) {
                            if (candidatePaths.getEleAtPos(j) == combinedPath) {
                                alreadyExists = true;
                                break;
                            }
                        }
                        
                        if (!alreadyExists) {
                            // 按权重顺序插入候选列表
                            int insertPos = 0;
                            while (insertPos < candidateWeights.getLength() && 
                                   candidateWeights.getEleAtPos(insertPos) < combinedWeight) {
                                insertPos++;
                            }
                            candidatePaths.insertEleAtPos(insertPos, combinedPath);
                            candidateWeights.insertEleAtPos(insertPos, combinedWeight);
                        }
                    }
                }
                
                // 恢复临时移除的边
                for (unsigned int e = 0; e < removedEdges.size(); e++) {
                    G.addEdge(removedEdges[e].first, removedEdges[e].second, removedWeights[e]);
                }
            }
        }
        
        // 输出结果
        printResults();
    }
    
    void banVertex(T vertex) {
        int pos = nodes.locateEle(vertex);
        if (pos != -1) {
            if_ban[pos] = true;
        }
    }
    
    void unbanVertex(T vertex) {
        int pos = nodes.locateEle(vertex);
        if (pos != -1) {
            if_ban[pos] = false;
        }
    }
    
    void setMaxTrans(int Y) {
        if (Y >= 0) {
            limit = Y;
        } else {
            limit = -1;
        }
    }
};



int main() {
    int m=0, n = 0;
    cin >> m >> n;
    VecList<string>strings;
    VecList<string>S1;
    VecList<string>S2;
    VecList<int>weight;
    for (int i = 0; i < m; i++)
    {
        string str;
        cin >> str;
        strings.insertLast(str);
    }


    vector<Edge<string>>edges;
    for(int i=0;i<n;i++)
    {
        string s1;
        string s2;
        int w;
        cin >> s1 >> s2 >> w;
        S1.insertLast(s1);
        S2.insertLast(s2);
        weight.insertLast(w);
        Edge<string>edge;
        edge.start = s1;
        edge.end = s2;
        edge.weight = w;
        edges.push_back(edge);
    }





    
    Solution<string> A(m, n,strings,edges);
    int** arr = A.G.getMatrix();


    bool isContinue=true;
    while (isContinue)
    {
            
            cout<<"Please enter your next request."<<endl;
            cout<<"Options include: ban X, unban X, maxTrans Y, paths A B k, quit."<<endl;
            string command;
            cin >> command;
            if (command == "ban") {
                string s;
                cin >> s;
                int pos = A.nodes.locateEle(s);
                if (pos != -1){
                    A.if_ban[pos] = true;
                }
             
            }
        
            else if (command == "unban") {
                string s;
                cin >> s;
                int pos = A.nodes.locateEle(s);
                if (pos != -1){
                    A.if_ban[pos] = false;
                }
            }
        
            else if (command == "maxTrans") {
                int Y;
                cin >> Y;
                if (Y >= 0)A.limit = Y;
                else A.limit = -1;
            }
            else if (command == "paths")
            {
                string start;
                string end;
                int k;
                cin >> start;
                cin >> end;
                cin >> k;
                A.minpaths(start, end, k);
            }
            else if (command == "quit") {
                return 0;
            }
            else{
            cout<<"No such option."<<endl;
        }
        
    }
    
    return 0;
}