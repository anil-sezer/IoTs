using MicroControllerApi.Database;
using Microsoft.AspNetCore.Diagnostics.HealthChecks;
using Microsoft.Extensions.Diagnostics.HealthChecks;

namespace MicroControllerApi.Extension;

public static class HealthCheckExtensions
{
    private const string ReadinessDbCheckName = "ReadinessDbCheck";
    
    public static void AddHealthChecksForEndpointAndDb(this WebApplicationBuilder builder)
    {
        builder.Services
            .AddHealthChecks()
            .AddDbContextCheck<ApiDbContext>(failureStatus: HealthStatus.Degraded, name: ReadinessDbCheckName);
    }

    public static void MapLivenessHealthCheck(this WebApplication app)
    {
        app.MapHealthChecks("/liveness", new HealthCheckOptions
        {
            Predicate = _ => false, // Always return healthy for liveness
            ResultStatusCodes =
            {
                [HealthStatus.Healthy] = StatusCodes.Status200OK,
                [HealthStatus.Degraded] = StatusCodes.Status200OK, // Liveness doesn't degrade
                [HealthStatus.Unhealthy] = StatusCodes.Status503ServiceUnavailable
            }
        });
    }

    public static void MapReadinessHealthCheck(this WebApplication app)
    {
        app.MapHealthChecks("/readiness", new HealthCheckOptions
        {
            Predicate = check => check.Name == ReadinessDbCheckName,
            ResultStatusCodes =
            {
                [HealthStatus.Healthy] = StatusCodes.Status200OK,
                [HealthStatus.Degraded] = StatusCodes.Status503ServiceUnavailable,
                [HealthStatus.Unhealthy] = StatusCodes.Status503ServiceUnavailable
            }
        });
    }
}
