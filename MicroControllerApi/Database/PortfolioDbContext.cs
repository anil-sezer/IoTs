using Microsoft.EntityFrameworkCore;

namespace MicroControllerApi.Database;

public class ApiDbContext : DbContext
{
    public ApiDbContext(DbContextOptions<ApiDbContext> options) : base(options)
    {
    }

    public DbSet<IotReport> IotReports { get; set; }
}
