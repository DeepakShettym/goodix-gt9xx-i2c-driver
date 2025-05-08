
static int my_driver_probe(struct platform_device *pdev)
{
    struct device_node *parent = pdev->dev.of_node;
    struct device_node *child;
    const char *value;
    int i = 0;

    // Iterate children to find the second one (index = 1)
    for_each_child_of_node(parent, child) {
        if (i == 1) {
            // Found second child (index 1)
            if (of_property_read_string(child, "prop1", &value) == 0) {
                dev_info(&pdev->dev, "Second child prop1 = %s\n", value);
            } else {
                dev_err(&pdev->dev, "prop1 not found in second child\n");
            }
            break;
        }
        i++;
    }

    return 0;
}
