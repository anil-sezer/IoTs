// ReSharper disable InconsistentNaming

using DotNetEnv;
using Serilog;

namespace MicroControllerApi.Extension;

/// <summary>
/// Provides direct access to environment variables with built-in type conversion
/// </summary>
public static class EnvVars
{
    // Business Logic
    public static short MINIMUM_TEMPERATURE => GetValue<short>("MINIMUM_TEMPERATURE");
    public static short MAXIMUM_TEMPERATURE => GetValue<short>("MAXIMUM_TEMPERATURE");
    public static int REPORT_INTERVAL => GetValue<int>("REPORT_INTERVAL");
    public static int TEMPERATURE_CHECK_INTERVAL => GetValue<int>("TEMPERATURE_CHECK_INTERVAL");
    public static int COOLDOWN_PERIOD => GetValue<int>("COOLDOWN_PERIOD");
    
    // Notification
    public static string NOTIFICATION_TELEGRAM_API_KEY => GetValue("NOTIFICATION_TELEGRAM_API_KEY");
    public static string NOTIFICATION_TELEGRAM_CHAT_ID => GetValue("NOTIFICATION_TELEGRAM_CHAT_ID");
    
    // Database
    public static string SQL_DB_HOST => GetValue("SQL_DB_HOST");
    public static string SQL_DB_PORT => GetValue("SQL_DB_PORT");
    public static string SQL_DB_USER => GetValue("SQL_DB_USER");
    public static string SQL_DB_PASSWORD => GetValue("SQL_DB_PASSWORD");
    public static string SQL_DB_NAME => GetValue("SQL_DB_NAME");
    
    // Environment
    public static string ASPNETCORE_ENVIRONMENT => GetValue("ASPNETCORE_ENVIRONMENT");
    public static bool IsDevelopment() => string.IsNullOrEmpty(ASPNETCORE_ENVIRONMENT) || 
                                          ASPNETCORE_ENVIRONMENT.Equals("Development", StringComparison.OrdinalIgnoreCase);
    
    public static void SetupEnvVariables(this WebApplicationBuilder builder)
    {
        if (builder.Environment.IsDevelopment())
            Env.Load(".env");
        
        // Trigger a get value to ensure that the env vars are loaded
        _ = ASPNETCORE_ENVIRONMENT;

        _ = SQL_DB_HOST;
        _ = SQL_DB_PORT;
        _ = SQL_DB_USER;
        _ = SQL_DB_NAME;
        _ = SQL_DB_PASSWORD;

        _ = NOTIFICATION_TELEGRAM_API_KEY;
        _ = NOTIFICATION_TELEGRAM_CHAT_ID;

        _ = MINIMUM_TEMPERATURE;
        _ = MAXIMUM_TEMPERATURE;
        _ = REPORT_INTERVAL;
        _ = TEMPERATURE_CHECK_INTERVAL;
        _ = COOLDOWN_PERIOD;
    }
    
    // Helper methods (internal implementation)
    private static string GetValue(string variableName)
    {
        return GetValue<string>(variableName);
    }

    private static T GetValue<T>(string variableName)
    {
        var val = Environment.GetEnvironmentVariable(variableName);

        if (string.IsNullOrEmpty(val))
        {
            Log.Error("This environment value is not set: {MissingValues}", variableName);
            throw new MissingEnvironmentValueException(variableName); 
        }

        try
        {
            return (T)Convert.ChangeType(val, typeof(T));
        }
        catch (Exception ex)
        {
            Log.Error(ex, "Failed to convert environment variable {VariableName} with value '{Value}' to type {Type}", 
                variableName, val, typeof(T).Name);
            throw new InvalidCastException($"Cannot convert environment variable '{variableName}' with value '{val}' to type {typeof(T).Name}", ex);
        }
    }
}
