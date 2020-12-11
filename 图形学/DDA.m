function DDA(x1,y1,x2,y2)

dx=(x2-x1);
dy=(y2-y1);

step=max(abs(dx),abs(dy));

deltax=dx/step;
deltay=dy/step;

x=x1;
y=y1;
hold on
for i=1:step
plot(round(x),round(y),'.')
pause(0.05)
x=x+deltax;
y=y+deltay;
end
hold off
end