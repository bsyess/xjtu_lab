function BresenhamLine(startX,startY,endX,endY)
    hold on;
    deltaX=endX-startX;
    deltaY=endY-startY;
    k=deltaY/deltaX;
    if k>=0
        x=startX;y=startY;
        if k<=1
            for x1=startX:endX
                y1=(deltaY/deltaX*(x1-startX) + startY)*deltaX;
                dist=y1-y*deltaX;
                dist=dist*2;
                if dist> deltaX ||dist<-deltaX
                    y=y+1;
                end
                plot(x1,y, 'r*');
                hold on;
                pause(0.05)
            end
        else
            for y1=startY:endY
                x1=((deltaX/deltaY*(y1-startY))+startX)*deltaY;
                dist=x1-x*deltaY;
                dist=dist*2;
                if dist> deltaY || dist<-deltaY
                    x=x+1;
                end
                plot(x,y1,'r*');
                hold on;
                pause(0.05)
            end
        end
    end
    if k<0
        x=endX;
        y=startY;
        if k>=-1
            for x1=startX:endX
                y1=(deltaY/deltaX*(x1-startX) +startY)*deltaX;
                dist=y1-y*deltaX;
                dist=dist*2;
                if dist> deltaX ||dist<-deltaX
                    y=y-1;
                end
                plot(x1,y, 'r*');
                hold on;
                pause(0.05)
            end
        else
            for y1=endY:startY
                x1=((deltaX/deltaY*(y1-startY))+startX)*deltaY;
                dist=x1-x*deltaY;
                dist=dist*2;
                if dist<deltaY || dist>-deltaY
                    x=x-1;
                end
                plot(x,y1,'r*');
                hold on;
                pause(0.05)
            end
        end
    end
