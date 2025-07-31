a = serial('COM5', 'BaudRate', 9600);
fopen(a); 
figure;
subplot(2,1,1);
distancePlot = animatedline('Color','b','LineWidth',2);
title('Distance');
xlabel('Time (s)');
ylabel('Dist (cm)');
grid on;
subplot(2,1,2);
speedPlot = animatedline('Color','r','LineWidth',2);
title('Speed');
xlabel('Time (s)');
ylabel('Spd(cm/s)');
grid on;
windowSize = 5;                          
distBuffer = zeros(1, windowSize);     
prevDist = 0;
startTime = tic;
prevTime = tic;
while true
    if a.BytesAvailable > 0
        distStr = fgetl(a);            
        rawDist = str2double(distStr); 
        if isnan(rawDist)              
            continue;
        end
        distBuffer = [distBuffer(2:end), rawDist];
        filteredDist = mean(distBuffer);
        currentTime = toc(startTime);
        dt = toc(prevTime);
        speed = abs(filteredDist - prevDist) / dt;
        subplot(2,1,1);
        addpoints(distancePlot, currentTime, filteredDist);
        drawnow limitrate;
        subplot(2,1,2);
        addpoints(speedPlot, currentTime, speed);
        drawnow limitrate;
        prevDist = filteredDist;
        prevTime = tic;
    end
    pause(0.05);
end