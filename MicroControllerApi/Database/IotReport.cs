using System.Text.Json;

namespace MicroControllerApi.Database;

public class IotReport : EntityBase
{
    public required string DeviceName { get; init; }
    public required JsonDocument Report { get; init; }
}
