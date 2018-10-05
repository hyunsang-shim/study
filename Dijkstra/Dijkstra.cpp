// Dijkstra.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#define MAX_POINTS 8



int map[MAX_POINTS][MAX_POINTS];
//std::vector<int> GetNextPoint(int start, int end, std::vector<int>);

int main()
{

	for (int i = 0; i < MAX_POINTS; i++)
		for (int j = 0; j < MAX_POINTS; j++)
			map[i][j] = INT_MAX;

	map[0][0] = 0;	map[0][1] = 2;	map[0][5] = 3;
	map[1][1] = 0;	map[1][0] = 2;	map[1][2] = 4;	map[1][3] = 1;
	map[2][2] = 0;	map[2][1] = 4;	map[2][4] = 3;
	map[3][3] = 0;	map[3][1] = 1;	map[3][4] = 3;	map[3][6] = 2;
	map[4][4] = 0;	map[4][2] = 3;	map[4][3] = 3;	map[4][7] = 4;
	map[5][5] = 0;	map[5][0] = 3;	map[5][6] = 6;
	map[6][6] = 0;	map[6][3] = 2;	map[6][5] = 5;	map[6][7] = 4;
	map[7][7] = 0;	map[7][4] = 4;	map[7][6] = 4;

	int toward = 0, start = 0, end = 0;

	std::cout << "경로 세팅 완료\n경로를 출력합니다.\n" << std::endl;
	for (int i = 0; i < MAX_POINTS; i++)
	{
		for (int j = 0; j < MAX_POINTS; j++)
		{
			if (i != j && map[i][j] != INT_MAX)
			{
				std::cout << i + 1 << "->" << j + 1 << "(cost : " << map[i][j] << ")\t";
			}
		}
		std::cout << std::endl;
	}


	// 각 지점이 연결되는 다음 지점을 리스트로 담는다.

	std::vector<std::vector<int> > routes;
	for (int i = 0; i < MAX_POINTS; i++)
	{
		routes.resize(i + 1);

		for (int j = 0; j < MAX_POINTS; j++)
		{
			if (map[i][j] < INT_MAX)
				routes[i].push_back(j);
		}
	}

	for (int i = 0; i < MAX_POINTS; i++)
	{
		std::cout << i + 1 << "\t->\t";
		for (int j = 0; j < routes[i].size(); j++)
		{
			if (routes[i][j] != INT_MAX)
				if (routes[i][j] != i)
					std::cout << routes[i][j] + 1 << "\t";
		}
		std::cout << std::endl;
	}

	std::cout << "시작 위치를 선택하세요. (1~8) : ";
	std::cin >> start;

	do {
		if (start > 8 || start < 1)
		{
			std::cout << "시작 위치는 1 ~ 8 중에서 골라야 합니다.\n다시 입력해 주세요 (1~8) : ";
			std::cin >> start;
		}

	} while (start > 8 || start < 1);

	std::cout << "목표 위치를 선택하세요. (1~8, 단, " << start << "제외) : ";
	std::cin >> end;

	do {
		if (end > 8 || end < 1 || start == end)
		{
			std::cout << "목표 위치는 1 ~ 8 중에서 골라야 합니다.\n다시 입력해 주세요 (1~8, 단, " << start << "제외) : ";
			std::cin >> end;
		}

	} while (end > 8 || end < 1 || start == end);


	std::cout << start << " 부터 " << end << " 까지의 최적 이동경로를 탐색합니다.\n";


	// 준비
	/*
	경로의 폐쇄 여부를 저장 할 배열 ( MAX_POINTS 크기, 기본값 = false)
	임시 방문 경로를 저장 할 배열(vector)
	임시 방문 경로의 코스트 값을 누적 시킬 정수형 변수
	최종 방문 경로를 저장 할 배열(vector)
	최종 방문 경로의 코스트 값을 누적 시킬 정수형 변수
	*/

	bool					isClosed[MAX_POINTS] = { false };
	std::vector<int>		tmpRoute(0);
	int						tmpCost(0);
	std::vector<int>		FinalRoute(0);
	int						FinalRoute(0);

	// 진행
	/*
	 임시 경로에 입력된 시작 지점을 추가한다.
	 (반복A)
	 임시 경로가 없을 경우, 전체 경로 중 폐쇄되지 않았고, 방문하지 않은 경로들을 찾는다.
	 남은 경로 수 확인
								-> 남은 경로 1개 이상 => 계속
								-> 남은 경로 0개 => 최종 방문 경로가 있는지 확인 -> 있음 : 종료
																			  -> 없음 : 예외 처리 출력(에러!)
	 남은 경로 중 index가 가장 작은 값을 임시 경로에 추가한다.
	 마지막 추가된 임시 경로가 가진 이동 가능한 경로를 확인한다. (폐쇄된 경로 제거, 최종 방문에 등록된 경로 제거)
								-> 이동 가능한 경로 있음 => 계속
								-> 이동 가능한 경로 없음 => 해당 경로를 폐쇄하고 임시 방문 경로를 초기화 한다. => 처음으로 돌아간다.
	 임시 경로에 선택된 경로를 추가한다.
	 임시 방문 코스트를 더한다.
	 목적지 도착 여부를 확인한다.
								-> 도착
									최종 방문 코스트와 비교한다 -> 같거나 작음 => 최종 코스트를 갱신한다.
																			=> 최종 경로를 갱신한다.
																			=> 임시 방문 경로를 초기화 한다.
																			=> 처음으로 돌아간다.
								-> 도착 아님 (반복 A)로 돌아감
	*/

	// 임시 경로에 입력된 시작 지점을 추가한다.
	tmpRoute.push_back(start);
	tmpCost = 0;

	while (1)
	{
		int CntRoute = 0;
		if (tmpRoute.empty())
		{
			for (int i = 0; i < MAX_POINTS; i++)
			{
				// 전체 경로 중 폐쇄되지 않았고, 방문하지 않은 경로들을 찾는다.
				if (!isClosed[i] && !FinalRoute[i])
					CntRoute++;
				else
				{
					// 남은 경로 중 index가 가장 작은 값을 임시 경로에 추가한다.
					tmpRoute.push_back(i);
					break;
				}
			}

			// 남은 경로 수 확인
			// -> 남은 경로 0개 = > 최종 방문 경로가 있는지 확인->있음 : 종료
			if (CntRoute == 0)
				break;



		}
		else
		{
			for (int i = 0; i < routes[start].size(); i++)
			{
				if (!isClosed[routes[start][i]]);

			}
		}


	}




	return 0;

}