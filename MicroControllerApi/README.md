dotnet ef migrations add MIGRATIONNAME --output-dir Migrations
dotnet ef migrations add FirstMigration --output-dir Migrations


ssh anilsezer@192.168.1.122 'cd /home/anilsezer/MicroControllers/MicroControllerApi && \
git pull && \
docker build -f ./Dockerfile -t imgregistry.anil-sezer.com/iot-api:latest . && \
docker push imgregistry.anil-sezer.com/iot-api:latest' && \
k rollout restart deployment iot-api-deployment -n iot