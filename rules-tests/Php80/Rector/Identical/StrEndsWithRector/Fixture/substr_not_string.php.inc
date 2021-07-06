<?php

namespace Rector\Tests\Php80\Rector\Identical\StrEndsWithRector\Fixture;

class SubstrNotString
{
    public function run()
    {
        $isNotMatch = substr($haystack, -5) !== 'value';

        $isNotMatch = 'value' !== substr($haystack, -5);
    }
}

?>
-----
<?php

namespace Rector\Tests\Php80\Rector\Identical\StrEndsWithRector\Fixture;

class SubstrNotString
{
    public function run()
    {
        $isNotMatch = !str_ends_with($haystack, 'value');

        $isNotMatch = !str_ends_with($haystack, 'value');
    }
}

?>
