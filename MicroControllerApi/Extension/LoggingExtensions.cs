using Serilog;
using Serilog.Events;

namespace MicroControllerApi.Extension;

public static class LoggingExtension
{
    public static void InitLogsWithSerilog(this WebApplicationBuilder builder)
    {
        Log.Logger = new LoggerConfiguration()
            .MinimumLevel.Debug()
            .MinimumLevel.Override("Microsoft", LogEventLevel.Information)
            .WriteTo.Console()
            // .WriteTo.OpenTelemetry(
            //     endpoint: "http://127.0.0.1:4318/v1/logs",
            //     protocol: OtlpProtocol.Grpc
            //     )
            .CreateLogger();
        builder.Host.UseSerilog();
        
        if(EnvVars.IsDevelopment())
            Log.Information("Can reach scalar on: https://localhost:8080/scalar");
    }
}
