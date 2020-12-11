function Bresenhamellipse(a,b)
x=0;
y=b;
d1=b*b+a*a*(-b+0.25);
while (b*b*(x+1)<a*a*(y-0.5))
plot(x,y,'.r','markersize',10);
hold on;pause(0.05);
plot(-x,-y,'.r','markersize',10);
hold on;pause(0.05);
plot(-x,y,'.r','markersize',10);
hold on;pause(0.05);
plot(x,-y,'.r','markersize',10);
hold on;pause(0.05);
    if d1<=0
        d1=d1+b*b*(2*x+3);
        x=x+1;
    else
        d1=d1+b*b*(2*x+3)+a*a*(-2*y+2);
        x=x+1;
        y=y-1;
    end
end

d2=b*b*(x+0.5)*(x+0.5)+a*a*(y-1)*(y-1)-a*a*b*b;
while y>=0
     plot(x,y,'.r','markersize',10);
     hold on;pause(0.05);
     plot(-x,-y,'.r','markersize',10);
     hold on;pause(0.05);
     plot(-x,y,'.r','markersize',10);
     hold on;pause(0.05);
     plot(x,-y,'.r','markersize',10);
     hold on;pause(0.05);
     if(d2<=0)
        d2=d2+b*b*(2*x+2)+a*a*(-2*y+3);
        x=x+1;
        y=y-1;
     else
        d2=d2+a*a*(-2*y+3);
        y=y-1;
     end
     grid on
end