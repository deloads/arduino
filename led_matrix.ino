int Grid[8][8] = {
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0}
};
int norchiftOutPut[]={0,0,1,0,1,0,0,1,1,1,0,1,0,0,1,1};
int chiftOutPut[] = {0,0,1,0,1,0,0,1,1,1,0,1,0,0,1,1};
int dc = 13;
int hc = 11;
int tc = 12;
int vrx = A0;
int vry = A1;
int sPin = 2;

void setup() {
  // put your setup code here, to run once:


  pinMode(dc,OUTPUT);
  pinMode(hc,OUTPUT);
  pinMode(tc,OUTPUT);
  pinMode(vrx,INPUT);
  pinMode(vry,INPUT);
  pinMode(sPin,INPUT);
  digitalWrite(sPin,HIGH);
}

void render(){
  digitalWrite(dc,LOW);
  digitalWrite(hc,LOW);
  digitalWrite(tc,LOW);

  for(int i = 15;i>-1;i--){
    digitalWrite(hc,LOW);
    if(chiftOutPut[i]==1){
      digitalWrite(dc,HIGH);
    }else{
      digitalWrite(dc,LOW);
    }
    digitalWrite(hc,HIGH);
  }
  digitalWrite(tc,HIGH);
}

int switchNumi(int num){
  bool done = true;
  if(num==0&&done){
    num = 3;
    done = false;
  }
  if(num==1&&done){
    num = 13;
    done = false;
  }
  if(num==2&&done){
    num = 12;
    done = false;
  }
  if(num==3&&done){
    num = 6;
    done = false;
  }
  if(num==4&&done){
    num = 10;
    done = false;
  }
  if(num==5&&done){
    num = 5;
    done = false;
  }
  if(num==6&&done){
    num = 1;
    done = false;
  }
  if(num==7&&done){
    num = 0;
    done = false;
  }

  return num;
}
int switchNumj(int num){
  bool done = true;
  if(num==0&&done){
    num = 11;
    done = false;
  }
  if(num==1&&done){
    num = 14;
    done = false;
  }
  if(num==2&&done){
    num = 9;
    done = false;
  }
  if(num==3&&done){
    num = 15;
    done = false;
  }
  if(num==4&&done){
    num = 4;
    done = false;
  }
  if(num==5&&done){
    num = 8;
    done = false;
  }
  if(num==6&&done){
    num = 2;
    done = false;
  }
  if(num==7&&done){
    num = 7;
    done = false;
  }

  return num;
}

void renderscreen(){


  for(int i = 0;i<8;i++){
    chiftOutPut[switchNumi(i)] = 1;
    for(int j = 0;j<8;j++){
      if(Grid[i][j]==1){
        chiftOutPut[switchNumj(j)] = 0;
      }
    }
    render();
    for(int j = 0;j<16;j++){
      chiftOutPut[j] = norchiftOutPut[j];
    }
  }
}

int signn(int num){
  int retu = 0;
  if(num<0){
    retu = -1;
  }
  if(num>0){
    retu = 1;
  }
  return retu;
}

int drawLine(int x1,int y1,int x2,int y2,int value){
  int x = x1;
  int y = y1;
  int delX = abs(x1-x2);
  int delY = abs(y1-y2);
  int s1 = signn(x2-x1);
  int s2 = signn(y2-y1);
  int inter = 0;
  if(delY>delX){
    int t = delX;
    delX = delY;
    delY = t;
    inter = 1;
  }
  int e = 2*delY-delX;
  int a = 2*delY;
  int b = 2*delY-2*delX;
  Grid[x1][y1] = value;
  for(int i=1;i<delX+1;i++){
    if(e<0){
      if(inter==1){
        y=y+s2;
      }else{
        x=x+s1;
      }
      e=e+a;
    }else{
      y=y+s2;
      x=x+s1;
      e=e+b;
    }
    Grid[x][y] = value;
  }
}

int xpos1 = 0;
int ypos1 = 0;
int xpos2 = 7;
int ypos2 = 7;
int count1 = 0;
int count2 = 0;
void loop() {
  count1++;
  if(count1 == 50){
    count2++;
    count1 = 0;
    drawLine(xpos1,ypos1,xpos2,ypos2,0);
    if(count2 == 15){
      count2 = 0;
      int xP = signn(xpos1-xpos2);
      int yP = signn(ypos1-ypos2);

      xpos2+=xP;
      ypos2+=yP;
    }
    xpos1+=random(-1,2);
    ypos1+=random(-1,2);
    if(xpos1==-1){
      xpos1=0;
    }
    if(xpos1==8){
      xpos1=7;
    }
    if(ypos1==-1){
      ypos1=0;
    }
    if(ypos1==8){
      ypos1=7;
    }
    if(xpos2==-1){
      xpos2=0;
    }
    if(xpos2==8){
      xpos2=7;
    }
    if(ypos2==-1){
      ypos2=0;
    }
    if(ypos2==8){
      ypos2=7;
    }

    drawLine(xpos1,ypos1,xpos2,ypos2,1);
  }


  renderscreen();
}
