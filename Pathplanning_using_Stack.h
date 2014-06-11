	// path planning에서 방향을 결정할 변수, status value 형태로 받을 예정, +x=1, +y=1, -x=3, -y=4
	Stack<int> stPointOfPathPlanning;

	while(1)
	{
		//목적지가 좌표상으로 더 낮은 곳에 있다면 연산 방향을 거꾸로 합니다
		if((nXGoal - nowX) <0)
			diffX = nowX -nXGoal;
		else
			diffX = nXGoal - nowX;

		if((nYGoal -nowY) <0)
			diffY = nowY - nYGoal;
		else
			diffY = nYGoal - nowY;
			
		if(diffX <0)
			diffX =0;
		if(diffY <0)
			diffY =0;

		if((diffX == 0) && (diffY == 0))
		{
			printf("루프종료");
			break;
		}	
//		pDC ->MoveTo(nowX, nowY);

		if((diffX - diffY) > 0)//+x방향으로 갈 길이 더 많으니 +x방향으로 갑니다
		{
			printf("diffX=%d\n", diffX);

		//목적지가 좌표상으로 더 낮은 곳에 있다면 -1연산을 합니다			
			if((nXGoal - nowX) < (unitOfRoad-1))
			{
				nowX -= unitOfRoad;
				path.push_back(LEFT); //stPointOfPathPlanning.push(LEFT); 
			}
			else
			{
				nowX += unitOfRoad;
				path.push_back(RIGHT);//stPointOfPathPlanning.push(RIGHT); 
			}
//			pDC ->LineTo(nowX, nowY);

		}
		//y의 갈길이 더 많다면 y를 택해서 갑니다
		else
		{
			printf(", diffY=%d\n", diffY);
			if((nYGoal -nowY) < (unitOfRoad-1))
			{
				nowY -= unitOfRoad;
				path.push_back(UP);//stPointOfPathPlanning.push(UP); 
			}
			else
			{
				nowY += unitOfRoad;
				path.push_back(DOWN);//stPointOfPathPlanning.push(DOWN); 
			}
//			pDC ->LineTo(nowX, nowY);

		}
	}

	//스택에 데이터 집어넣기, 역순으로 집어넣어야 스택에는 정방향으로 출력됩니다.
	for(int i=path.size()-1 ; i> 0  ; i--)
	{
		stPointOfPathPlanning.push(path[i]);
	}
	//path 초기화 
	path.clear();
/*
	for(int i = 0 ;  i<path.size()-1  ; i++)
	{
		printf("%d, ", stPointOfPathPlanning.pop());
	}
*/

	//라인 그리기 전 초기화
	nowX = nXstart;
	nowY = nYstart;


	//스택은 거꾸로 꺼내지지만 데이터를 넣을 당시에 역순으로 넣어주어서 정방향 출력을 합니다.
	while(!stPointOfPathPlanning.isEmpty())
	{
		int movePointStack;

		//선그리기 전 출발 좌표 지정
		pDC ->MoveTo(nowX, nowY);

		//스택에 데이터 받기
		movePointStack = stPointOfPathPlanning.pop();
		if(movePointStack == RIGHT)
		{//	printf("right, ");
			nowX = (nowX + unitOfRoad); 		
			pDC ->LineTo(nowX, nowY);
		}
		else if(movePointStack == LEFT)
		{//	printf("left, ");
			nowX = (nowX - unitOfRoad);
			pDC ->LineTo(nowX, nowY);

		}
		else if(movePointStack == DOWN)
		{//	printf("down, ");
			nowY = (nowY + unitOfRoad);
			pDC ->LineTo(nowX, nowY);
		}
		else if(movePointStack == UP)
		{//	printf("up, ");
			nowY = (nowY - unitOfRoad);
			pDC ->LineTo(nowX, nowY+1);
		}
	}
