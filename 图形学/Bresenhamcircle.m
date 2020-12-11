function Bresenhamcircle(xc,yc,r)
x=0;
y=r;
p=3-2*r;
hold on
grid minor
while(x<y)
    plot(xc+x,yc+y,'r*')
    hold on;pause(0.05);
    plot(xc-x,yc+y,'r*')
    hold on;pause(0.05);
    plot(xc+x,yc-y,'r*')
    hold on;pause(0.05);
    plot(xc-x,yc-y,'r*')
    hold on;pause(0.05);
    plot(xc+y,yc+x,'r*')
    hold on;pause(0.05);
    plot(xc-y,yc+x,'r*')
    hold on;pause(0.05);
    plot(xc+y,yc-x,'r*')
    hold on;pause(0.05);
    plot(xc-y,yc-x,'r*')
    hold on;pause(0.05);
    if(p<0)
        p=p+4*x+6;
    else
        p=p+4*(x-y)+10;
        y=y-1;
    end
    x=x+1;
end
if(x==y)
    plot(xc+x,yc+y,'r*')
    hold on;pause(0.05);
    plot(xc-x,yc+y,'r*')
    hold on;pause(0.05);
    plot(xc+x,yc-y,'r*')
    hold on;pause(0.05);
    plot(xc-x,yc-y,'r*')
    hold on;pause(0.05);
    plot(xc+y,yc+x,'r*')
    hold on;pause(0.05);
end
hold off
end