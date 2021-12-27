TEMPLATE = subdirs

SUBDIRS += \
    custom_setting \
    test_custom_setting

test_custom_setting.depends = custom_setting
