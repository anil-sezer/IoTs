using MicroControllerApi.Controller.Dto;
using MicroControllerApi.Database;
using MicroControllerApi.Extension;
using Microsoft.AspNetCore.Mvc;

namespace MicroControllerApi.Controller;

[ApiController]
[Route("[controller]")]
public class IotController(ApiDbContext dbContext) : ControllerBase
{
    // {"MinTemp":20,"MaxTemp":23,"ReportInterval":60000,"TempCheckInterval":5000,"CooldownPeriod":600000}
    [HttpGet(Name = "Directives")]
    public ActionResult<DirectivesResponse> Get()
    {
        return Ok(new DirectivesResponse
        {
            MinTemp = EnvVars.MINIMUM_TEMPERATURE,
            MaxTemp = EnvVars.MAXIMUM_TEMPERATURE,
            ReportInterval = EnvVars.REPORT_INTERVAL,
            TempCheckInterval = EnvVars.TEMPERATURE_CHECK_INTERVAL,
            CooldownPeriod = EnvVars.COOLDOWN_PERIOD
        });
    }
    
    // String body = "{\"DeviceName\": \"Kegerator\",\"Report\": {\"Temp\":" + tempAsString + ",\"IsFridgeIsOn\":" + isFridgeIsOnAsString + "} }";
    [HttpPost(Name = "ReportState")]
    public async Task<IActionResult> Set([FromBody] ReportRequest request)
    {
        dbContext.IotReports.Add(new IotReport
        {
            DeviceName = request.DeviceName,
            Report = request.Report
        });
        await dbContext.SaveChangesAsync();
        
        return Ok();
    }
}
