def merge_configs(platformio_ini, local_config_ini):
    # Read platformio.ini content
    pio_config = read_config(platformio_ini)

    # Read local_config.ini content
    local_config = read_config(local_config_ini)

    # Extract build flags from local_config
    build_flags = ""
    for line in local_config.splitlines():
        if line.strip():
            key, value = line.split('=', 1)
            build_flags += f' -D{key}=\"{value}\"'

    # Append or replace build flags in platformio.ini
    lines = pio_config.splitlines()
    for i, line in enumerate(lines):
        if line.startswith('build_flags ='):
            lines[i] = 'build_flags =' + build_flags
            break
    else:  # 'build_flags' section not found; add it
        lines.append('build_flags =' + build_flags)

    # Write the merged configuration back to platformio.ini
    write_config(platformio_ini, '\n'.join(lines))

if __name__ == "__main__":
    merge_configs('platformio.ini', 'local_config.ini')
