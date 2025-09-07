using System.Text.Json;

namespace MicroControllerApi.Controller.Dto;

public class ReportRequest
{
    public required string DeviceName { get; init; }
    public required JsonDocument Report { get; init; }
}
