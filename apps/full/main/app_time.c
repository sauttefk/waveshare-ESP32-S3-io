#include "app_time.h"
#include "app_config.h"
#include "scripting.h"

#include <stdlib.h>
#include <time.h>
#include <esp_log.h>

#define TAG "app_time"

void app_time_apply_tz(void)
{
    const app_config_t *cfg = app_config_get();
    /* "UTC0" is the POSIX spelling of UTC; an empty config means "no local offset". */
    const char *tz = cfg->tz[0] ? cfg->tz : "UTC0";
    setenv("TZ", tz, 1);
    tzset();
    scripting_on_tz_change();   /* cron timers already armed carry the old offset */
    ESP_LOGI(TAG, "timezone applied: TZ=%s", tz);
}
